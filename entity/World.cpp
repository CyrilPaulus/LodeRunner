/* 
 * File:   World.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 6:47 PM
 */

#include "World.h"
#include <stdio.h>
#include <iostream>

World::World() {    
    player = new Character(this);
    player->SetColor(sf::Color(0,0,255));
    width = 0;
    height = 0;
    completed = false;
    ai = new AiAgent(this);
}


World::~World() {
    Clean();    
    delete player;
    delete ai;
}

void World::Clean() {
    std::vector<Block*>::iterator it;
    for(it = blocks.begin(); it != blocks.end(); it++)
        free(*it);
    
    std::vector<Goal*>::iterator git;     
    for(git = goals.begin(); git != goals.end(); git++)
        free(*git);
    
    std::vector<Character*>::iterator enm;     
    for(enm = enemies.begin(); enm != enemies.end(); enm++)
        free(*enm);
    
 
    
    blocks.empty();
    goals.empty();
    completed = false;
}

void World::Draw(sf::RenderTarget* rt) {
          
    std::vector<Block*>::iterator it;     
    for(it = blocks.begin(); it != blocks.end(); it++)
        (*it)->Draw(rt);
    
    std::vector<Goal*>::iterator git;     
    for(git = goals.begin(); git != goals.end(); git++)
        (*git)->Draw(rt);
    
    std::vector<Character*>::iterator enm;     
    for(enm = enemies.begin(); enm != enemies.end(); enm++)
        (*enm)->Draw(rt);   
    
    player->Draw(rt);
}

void World::Update(unsigned int frametime, Input input) {
    std::vector<Block*>::iterator it;
    for(it = blocks.begin(); it != blocks.end(); it++){
        (*it)->Update(frametime);
        (*it)->SetColor(sf::Color(255,255,255));
    }
    player->Update(frametime, input);
    
    std::vector<Character*>::iterator cit;
    for(cit = enemies.begin(); cit != enemies.end(); cit++)
        (*cit)->Update(frametime, ai->GenerateInput(*cit, player));
    
    std::vector<Goal*>::iterator git;     
    for(git = goals.begin(); git != goals.end(); git++)
        if(player->GetBbox().Intersects((*git)->GetBbox())) {
            delete(*git);
            git = goals.erase(git);
            git--;            
        }
    
    if(goals.size() == 0 && !completed) {
        completed = true;
        for(it = blocks.begin(); it != blocks.end(); it++)
            if((*it)->GetType() == Block::ENDLADDER)
                (*it)->SetActive(true);
    }
    
  
}

void World::LoadFromFile(char* filename) {
    Clean();
    FILE *f = fopen(filename, "r");
    if (!f) {
        std::cerr << "Can't load file: " << filename << std::endl;
        return;
    }

    fscanf(f, "d%dx%d\n", &width, &height);
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int value;
            fscanf(f, "%1d", &value);

            //BLOCK
            Block* b = NULL;
            if (value >= 1 && value <= 6)
                b = new Block(value);
            else
                b = new Block(Block::EMPTY);

            b->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));
            blocks.push_back(b);


            if (value == 9)
                player->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));

            else if (value == 8) {
                Character* en = new Character(this);
                en->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));
                en->SetSpeed(sf::Vector2f(75, 75));
                enemies.push_back(en);
            } else if (value == 7) {
                Goal* g = new Goal();
                g->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));
                goals.push_back(g);
            }
        }
        fscanf(f, "\n");
    }
    fclose(f);
}

Block* World::GetCollidingSolid(sf::FloatRect bbox) {

    for(int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for(int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {
            if(i >= 0 && j >= 0 && i < width && j < height) {
                Block *candidate = blocks[j * width + i];          
                if (candidate->GetBbox().Intersects(bbox) && candidate->IsSolid() ) {            
                return candidate;
            }
        }
    }
    
    return NULL;
}

Block* World::GetCollidingLadder(sf::FloatRect bbox) {

    for(int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for(int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {
            if(i >= 0 && j >= 0 && i < width && j < height) {
                Block *candidate = blocks[j * width + i];          
                if (candidate->GetBbox().Intersects(bbox) && candidate->IsLadder() ) {            
                return candidate;
            }
        }
    }
    
    return NULL;
}

Block* World::GetCollidingRope(sf::FloatRect bbox) {

    for(int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for(int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {
            if(i >= 0 && j >= 0 && i < width && j < height) {
                Block *candidate = blocks[j * width + i];          
                if (candidate->GetBbox().Intersects(bbox) && candidate->IsRope() ) {            
                return candidate;
            }
        }
    }
    
    return NULL;
}

sf::Vector2f World::GetSize() {
    return sf::Vector2f(width * Block::WIDTH, height * Block::HEIGHT);
}

bool World::IsUnderRope(int x, int y) {
    for(int j = y - 1; j > 0; j--) {
        if(blocks[j*width + x]->GetType() == Block::ROPE)
            return true;
        else if(blocks[j*width+x]->IsSolid())
            break;
    }
    return false;
}

std::list<Block*> World::GetNeighbors(int x, int y) {
    std::list<Block*> value;
    Block* current = blocks[y * width + x];
    bool isSolidUnderCurrent = false;
    if (y + 1 < height ) 
        isSolidUnderCurrent = blocks[(y+1) * width + x]->IsSolid() || blocks[(y+1) * width + x]->IsLadder();
    
    int xs[] = {x, x - 1, x + 1, x};
    int ys[] = {y - 1, y, y, y + 1};

   
    for (int i = 0; i < 4; i++) {
       
        if (xs[i] < 0 || xs[i] >= width || ys[i] < 0 || ys[i] >= height)
            continue;
                 
        Block* candidate = blocks[ys[i] * width + xs[i]];

        if ((candidate->IsLadder() || candidate->IsRope()) && (i == 1 || i == 2))
            value.push_back(candidate);
        else if (!candidate->IsSolid() && (i == 1 || i == 2) &&
                (current->IsLadder() || current->IsRope() || isSolidUnderCurrent)) 
            value.push_back(candidate);       
        else if (!candidate->IsSolid() && i == 3)
            value.push_back(candidate);
        else if (!(candidate->IsSolid()) && i == 0
                && current->IsLadder())
            value.push_back(candidate);
    }
    return value;
}

Block* World::GetBlock(int x, int y) {
    if(x >= 0 && x < width && y >= 0 && y < height)
        return blocks[y*width + x];
    else
        return NULL;
}