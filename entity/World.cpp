/* 
 * File:   World.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 6:47 PM
 */

#include "World.h"
#include <stdio.h>
#include <iostream>

World::World(ImageManager *imgManager) {
    this->imgManager = imgManager;
    player = new Character(imgManager, this);
    width = 0;
    height = 0;
}


World::~World() {
    std::vector<Block*>::iterator it;
    for(it = blocks.begin(); it != blocks.end(); it++)
        free(*it);
    delete player;
}

void World::Draw(sf::RenderTarget* rt) {
    
       
    std::vector<Block*>::iterator it;
    
     
    for(it = blocks.begin(); it != blocks.end(); it++)
        (*it)->Draw(rt);
    player->Draw(rt);
}

void World::Update(unsigned int frametime, Input input) {
    std::vector<Block*>::iterator it;
    for(it = blocks.begin(); it != blocks.end(); it++)
        (*it)->Update(frametime);
    
    player->Update(frametime, input);
}

void World::LoadFromFile(char* filename) {
    FILE *f = fopen(filename, "r");
    if(!f) {
        std::cerr << "Can't load file: " << filename << std::endl;
        return;
    }
    
    fscanf(f, "d%dx%d\n", &width, &height);
    for(int j = 0; j < height; j++) {
        for(int i = 0; i < width; i++) {
            int value;
            fscanf(f, "%1d", &value);
            
            //BLOCK
             Block* b = NULL;
            if(value >= 1 && value <= 6) 
                b = new Block(imgManager, value);
             else 
                b = new Block(imgManager, Block::EMPTY);
 
            b->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));
            blocks.push_back(b);
        }
        fscanf(f, "\n");
    }
    fclose(f);
}

Block* World::GetCollidingSolid(sf::FloatRect bbox) {

    for(int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for(int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {
            Block *candidate = blocks[j * width + i];          
            if (candidate->GetBbox().Intersects(bbox) && candidate->IsSolid() ) {            
            return candidate;
        }
    }
    
    return NULL;
}

Block* World::GetCollidingLadder(sf::FloatRect bbox) {

    for(int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for(int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {
            Block *candidate = blocks[j * width + i];          
            if (candidate->GetBbox().Intersects(bbox) && candidate->IsLadder() ) {            
            return candidate;
        }
    }
    
    return NULL;
}

Block* World::GetCollidingRope(sf::FloatRect bbox) {

    for(int j = bbox.Top / Block::HEIGHT; j <= (bbox.Top + bbox.Height) / Block::HEIGHT; j++)
        for(int i = bbox.Left / Block::WIDTH; i <= (bbox.Left + bbox.Width) / Block::WIDTH; i++) {
            Block *candidate = blocks[j * width + i];          
            if (candidate->GetBbox().Intersects(bbox) && candidate->IsRope() ) {            
            return candidate;
        }
    }
    
    return NULL;
}

sf::Vector2f World::GetSize() {
    return sf::Vector2f(width * Block::WIDTH, height * Block::HEIGHT);
}

