/* 
 * File:   Block.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 6:03 PM
 */

#include <SFML/System/Time.hpp>
#include <list>

#include "Entity.h"
#include "Block.h"
#include "World.h"
#include "Character.h"


const char* Block::file[] = {"map/empty", "map/wall", "map/cement", "map/ladder", 
                                "map/slide", "map/wall", "map/ladder"};

Block::Block(int type) : Entity(){
    this->type = type;
    //if(type != Block::EMPTY)
        image->setTexture(*ImageManager::getInstance()->getImage(file[type]));
    setBBox(sf::Vector2f(Block::WIDTH, Block::HEIGHT));
    if(type == Block::ENDLADDER)
        active = false;
    else
        active = true;
    timer = sf::seconds(0);
    trapped = NULL;
}

void Block::update(sf::Time frametime, World *world) {
    if(!active && type == Block::WALL){
        timer += frametime;
        
        if(trapped == NULL) {
            std::list<Character*> ennemies = world->getEnnemies();
            std::list<Character*>::iterator en;
            for(en = ennemies.begin(); en != ennemies.end(); en++) {
                if((*en)->getBbox().intersects(getBbox()) && (*en)->getPosition().y >= position.y){
                    (*en)->setMoveable(false);
                    trapped = (*en);
                }
            }
        }
        
        if(timer >= sf::seconds(10)){
            timer = sf::Time::Zero;
            active = true;
            if(trapped) {
                trapped->setMoveable(true);
                trapped->resetToOrigin();
                trapped = NULL;
            }
        }
            
    }
    
}

int Block::getType() {
    return type;
}

void Block::draw(sf::RenderTarget* rt) {
    if(active)
        Entity::draw(rt);
}

bool Block::isSolid() {
    return (active || trapped != NULL) && (type == Block::CEMENT || type == Block::WALL);
}

bool Block::isAiSolid() {
    return (type == Block::CEMENT || type == Block::WALL);
}

bool Block::isLadder() {
    return (type == Block::LADDER || type == Block::ENDLADDER) && active;
}

bool Block::isRope() {
    return type == Block::ROPE;
}

void Block::setActive(bool active) {
    this->active = active;
}



