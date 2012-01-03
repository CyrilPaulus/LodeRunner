/* 
 * File:   Block.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 6:03 PM
 */

#include "Entity.h"
#include "Block.h"


const char* Block::file[] = {"", "map/wall", "map/cement", "map/ladder", 
                                "map/slide", "map/wall", "map/ladder"};

Block::Block(ImageManager* imgManager, int type) : Entity(imgManager){
    this->type = type;
    if(type != Block::EMPTY)
        image->SetTexture(*imgManager->get(file[type]));
    SetBBox(sf::Vector2f(Block::WIDTH, Block::HEIGHT));
}

void Block::Update(unsigned int time) {
    
}

bool Block::IsSolid() {
    return type == Block::CEMENT || type == Block::WALL;
}



