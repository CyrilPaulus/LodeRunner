/* 
 * File:   Block.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 6:03 PM
 */

#include <SFML/System/Time.hpp>

#include "Entity.h"
#include "Block.h"


const char* Block::file[] = {"map/empty", "map/wall", "map/cement", "map/ladder", 
                                "map/slide", "map/wall", "map/ladder"};

Block::Block(int type) : Entity(){
    this->type = type;
    //if(type != Block::EMPTY)
        image->SetTexture(*ImageManager::getInstance()->get(file[type]));
    SetBBox(sf::Vector2f(Block::WIDTH, Block::HEIGHT));
    if(type == Block::ENDLADDER)
        active = false;
    else
        active = true;
    timer = sf::Seconds(0);
}

void Block::Update(sf::Time frametime) {
    if(!active && type == Block::WALL){
        timer += frametime;
        if(timer >= sf::Seconds(3)){
            timer = sf::Seconds(0);
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



