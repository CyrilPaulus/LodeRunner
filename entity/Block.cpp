/* 
 * File:   Block.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 6:03 PM
 */

#include "Entity.h"
#include "Block.h"


const char* Block::file[] = {"map/empty", "map/wall", "map/cement", "map/ladder", 
                                "map/slide", "map/wall", "map/ladder"};

Block::Block(int type) : Entity(){
    this->type = type;
    //if(type != Block::EMPTY)
        image->SetTexture(*ImageManagerSingleton::GetInstance()->get(file[type]));
    SetBBox(sf::Vector2f(Block::WIDTH, Block::HEIGHT));
    if(type == Block::ENDLADDER)
        active = false;
    else
        active = true;
    timer = 0;
}

void Block::Update(unsigned int time) {
    if(!active && type == Block::WALL){
        timer += time / (float)1000;
        if(timer >= 3){
            timer = 0;
            active = true;
        }
            
    }
    
}

int Block::GetType() {
    return type;
}

void Block::Draw(sf::RenderTarget* rt) {
    if(active)
        Entity::Draw(rt);
}

bool Block::IsSolid() {
    return active && (type == Block::CEMENT || type == Block::WALL);
}

bool Block::IsLadder() {
    return (type == Block::LADDER || type == Block::ENDLADDER) && active;
}

bool Block::IsRope() {
    return type == Block::ROPE;
}

void Block::SetActive(bool active) {
    this->active = active;
}



