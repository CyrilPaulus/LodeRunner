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
}


World::~World() {
    std::vector<Block*>::iterator it;
    for(it = blocks.begin(); it != blocks.end(); it++)
        free(*it);
}

void World::Draw(sf::RenderTarget* rt) {
    std::vector<Block*>::iterator it;
    for(it = blocks.begin(); it != blocks.end(); it++)
        (*it)->Draw(rt);
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
            if(value >= 1 && value <= 6) {
                Block* b = new Block(imgManager, value);
                b->SetPosition(sf::Vector2f(i * Block::WIDTH, j * Block::HEIGHT));
                blocks.push_back(b);
            }
        }
        fscanf(f, "\n");
    }
    fclose(f);
}

