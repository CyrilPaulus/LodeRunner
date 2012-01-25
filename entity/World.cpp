/* 
 * File:   World.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 6:47 PM
 */

#include "World.h"
#include <stdio.h>
#include <iostream>

#include "../ai/AiManager.h"
#include "../entity/Block.h"
#include "../entity/Character.h"
#include "../entity/Goal.h"

World::World() {
    player = new Character(this);
    player->SetColor(sf::Color(0, 0, 255));
    width = 0;
    height = 0;
    completed = false;
    ai = new AiManager(this);
}

World::~World() {
    delete ai;
    Clean();
    delete player;

}

void World::Clean() {
    delete ai;
    std::vector<Block*>::iterator it;
    for (it = blocks.begin(); it != blocks.end(); it++)
        free(*it);

    std::vector<Goal*>::iterator git;
    for (git = goals.begin(); git != goals.end(); git++)
        free(*git);

    std::vector<Character*>::iterator enm;
    for (enm = enemies.begin(); enm != enemies.end(); enm++)
        free(*enm);

    blocks.clear();
    goals.clear();
    enemies.clear();
    completed = false;
    ai = new AiManager(this);
}

void World::Draw(sf::RenderTarget* rt) {

    std::vector<Block*>::iterator it;
    for (it = blocks.begin(); it != blocks.end(); it++)
        (*it)->Draw(rt);

    std::vector<Goal*>::iterator git;
    for (git = goals.begin(); git != goals.end(); git++)
        (*git)->Draw(rt);

    std::vector<Character*>::iterator enm;
    for (enm = enemies.begin(); enm != enemies.end(); enm++)
        (*enm)->Draw(rt);

    player->Draw(rt);
}

void World::Update(unsigned int frametime, Input input) {
    std::vector<Block*>::iterator it;
    for (it = blocks.begin(); it != blocks.end(); it++) {
        (*it)->Update(frametime);
        (*it)->SetColor(sf::Color(255, 255, 255));
    }
    player->Update(frametime, input);

    std::vector<Character*>::iterator cit;
    for (cit = enemies.begin(); cit != enemies.end(); cit++)
        (*cit)->Update(frametime, ai->Update((*cit), frametime));

    std::vector<Goal*>::iterator git;
    for (git = goals.begin(); git != goals.end(); git++)
        if (player->GetBbox().Intersects((*git)->GetBbox())) {
            delete(*git);
            git = goals.erase(git);
            git--;
        }

    if (goals.size() == 0 && !completed) {
        completed = true;
        for (it = blocks.begin(); it != blocks.end(); it++)
            if ((*it)->GetType() == Block::ENDLADDER)
                (*it)->SetActive(true);
    }


}

void World::LoadFromFile(std::string filename) {
    Clean();
    FILE *f = fopen(filename.c_str(), "r");
    if (!f) {
        std::cerr << "Can't load file: " << filename << std::endl;
        return;
    }

    fscanf(f, "d%dx%d\n", &width, &height);

    width += 2;
    height += 2;
    for (int i = 0; i < width; i++)
        PushBlock(i, 0, Block::CEMENT);

    for (int j = 1; j < height - 1; j++) {
        PushBlock(0, j, Block::CEMENT);

        for (int i = 1; i < width - 1; i++) {

            int value;
            fscanf(f, "%1d", &value);

            //BLOCK
            PushBlock(i, j, value);

            if (value == 9)
                player->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));

            else if (value == 8) {
                Character* en = new Character(this);
                en->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));
                en->SetSpeed(sf::Vector2f(175, 150));
                enemies.push_back(en);
                ai->AddAgent(en);
            } else if (value == 7) {
                Goal* g = new Goal();
                g->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));
                goals.push_back(g);
            }
        }
        fscanf(f, "\n");
        PushBlock(width - 1, j, Block::CEMENT);
    }
    for (int i = 0; i < width; i++)
        PushBlock(i, height - 1, Block::CEMENT);
    fclose(f);
}

Block* World::GetCollidingSolid(sf::FloatRect bbox) {

    for (int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for (int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {
            Block *candidate = GetBlock(i, j);
            if (candidate->GetBbox().Intersects(bbox) && candidate->IsSolid()) {
                return candidate;

            }
        }

    return NULL;
}

Character* World::GetCollidingEnnemy(sf::FloatRect bbox) {
std::vector<Character*>::iterator enm;
    for (enm = enemies.begin(); enm != enemies.end(); enm++)
        if((*enm)->GetBbox().Intersects(bbox))
            return *enm;
    
    return NULL;
}

Block* World::GetCollidingLadder(sf::FloatRect bbox) {

    for (int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for (int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {

            Block *candidate = GetBlock(i, j);
            if (candidate->GetBbox().Intersects(bbox) && candidate->IsLadder()) {
                return candidate;

            }
        }

    return NULL;
}

Block* World::GetCollidingRope(sf::FloatRect bbox) {

    for (int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for (int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {

            Block *candidate = GetBlock(i, j);
            if (candidate->GetBbox().Intersects(bbox) && candidate->IsRope()) {
                return candidate;

            }
        }

    return NULL;
}

sf::Vector2f World::GetSize() {
    return sf::Vector2f(width * Block::WIDTH, height * Block::HEIGHT);
}

bool World::IsUnderRope(int x, int y) {
    for (int j = y - 1; j > 0; j--) {
        if (GetBlock(x, j)->GetType() == Block::ROPE)
            return true;
        else if (GetBlock(x, j)->IsSolid())
            break;
    }
    return false;
}

std::list<Block*> World::GetNeighbors(int x, int y) {
    std::list<Block*> value;
    Block* current = GetBlock(x, y);
    bool isSolidUnderCurrent = false;
    if (y + 1 < height)
        isSolidUnderCurrent = GetBlock(x, y + 1)->IsSolid() || GetBlock(x, y + 1)->IsLadder();

    int xs[] = {x, x - 1, x + 1, x};
    int ys[] = {y - 1, y, y, y + 1};


    for (int i = 0; i < 4; i++) {

        if (xs[i] < 0 || xs[i] >= width || ys[i] < 0 || ys[i] >= height)
            continue;

        Block* candidate = GetBlock(xs[i], ys[i]);

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
    //Need to offset for the border
    return blocks[y * width + x];

}

Character* World::GetPlayer() {
    return player;
}

void World::PushBlock(int i, int j, int value) {
    Block* b = NULL;
    if (value >= 1 && value <= 6)
        b = new Block(value);
    else
        b = new Block(Block::EMPTY);

    b->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));
    blocks.push_back(b);
}

