/* 
 * File:   Block.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 6:03 PM
 */

#include "Entity.h"
#include "Block.h"


const char* Block::file[] = {"map/wall", "map/cement", "map/slide", "map/ladder"};

Block::Block(ImageManager* imgManager, int type) : Entity(imgManager){
    this->type = type;
    image->SetTexture(*imgManager->get(file[type]));
}

void Block::Update(unsigned int time) {
    
}



