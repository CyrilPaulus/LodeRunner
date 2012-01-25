/* 
 * File:   Character.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 8:08 PM
 */

#include "Character.h"
#include "Block.h"
#include "World.h"
#include <math.h>
Character::Character(World *w) : Entity() {
    image->SetTexture(*ImageManager::getInstance()->getImage("them"));
    setBBox(sf::Vector2f(24, 30));
    speed = sf::Vector2f(250,150);
    isFalling = false;
    canFall = true;
    isHanging = false;
    isClimbing = false;
    world = w;
    direction = sf::Vector2f(0, 0);
}

void Character::update(sf::Time frametime, Input input) {
    
    int x0 = position.x / Block::WIDTH;
    int y0 = position.y / Block::HEIGHT;
    float seconds = frametime.AsSeconds();
    
    //Carve
    if(input.LeftCarve) {
        Block* b = world->getBlock(x0 - 1, y0 + 1);
        Block* c = world->getBlock(x0 - 1, y0 );
        if(b && b->getType() == Block::WALL && !c->isSolid() && !c->isLadder() && !c->isRope())
            b->setActive(false);
    }
    
    if(input.RightCarve) {
        Block* b = world->getBlock(x0 + 1, y0 + 1);
        Block* c = world->getBlock(x0 + 1, y0);
        if(b && b->getType() == Block::WALL && !c->isSolid() && !c->isLadder() && !c->isRope())
            b->setActive(false);
    }
    
    sf::Vector2f direction = sf::Vector2f(0, 0);
    Block* rope = world->getCollidingRope(getBbox());
    Block* ladder = world->getCollidingLadder(getBbox());

    bool isCentring = false;
    if (ladder && (fabs(ladder->getCenter().x - getCenter().x) < 4)) {

        isClimbing = true;
        if (input.Up)
            direction -= sf::Vector2f(0, speed.y);
        else if (input.Down)
            direction += sf::Vector2f(0, speed.y);
        
        
        if(input.Up || input.Down){
	  setPosition(sf::Vector2f(ladder->getPosition().x + 1/2* (ladder->getBbox().Width - getBbox().Width), getPosition().y));
	  isCentring = true;
	}
    } else if (!ladder) {
        isClimbing = false;
    }    

    //Align to rope
    if (rope && (input.Left || input.Right || isFalling) && !(input.Down)) {
        isHanging = true;

        int deltaY = rope->getPosition().y - getPosition().y;
        if (abs(deltaY) < 4)
            setPosition(sf::Vector2f(position.x, rope->getPosition().y));
    }
    
    
    if (!rope || input.Down || rope->getPosition().y != getPosition().y)
        isHanging = false;
    
    if(isClimbing && isHanging)
        isClimbing = false;
    
    if(!isHanging && !isClimbing)
        isFalling = true;
    else
        isFalling = false;
    
     if(isFalling) 
        direction += sf::Vector2f(0, speed.y);       
    
    if (direction.y != 0) {
        setPosition(sf::Vector2f(position.x, position.y + direction.y * seconds));
              
        Entity *b = world->getCollidingSolid(getBbox());
        if (b != NULL) {
            if (direction.y < 0)
                setPosition(sf::Vector2f(position.x, b->getBbox().Top + b->getBbox().Height));
            else {
                setPosition(sf::Vector2f(position.x, b->getBbox().Top - getBbox().Height));
                isFalling = false;
            }
        }
        
        /*b = world->GetCollidingEnnemy(GetBbox());
        if (b != NULL && b != this) {
            if (direction.y < 0)
                SetPosition(sf::Vector2f(position.x, b->GetBbox().Top + b->GetBbox().Height));
            else {
                SetPosition(sf::Vector2f(position.x, b->GetBbox().Top - GetBbox().Height));
                isFalling = false;
            }
        }*/
        
        //Special case to walk on ladder
        ladder = world->getCollidingLadder(getBbox());
        if(ladder && direction.y > 0  && isFalling && ladder->getPosition().y > position.y) {
            if(!input.Down)
                setPosition(sf::Vector2f(position.x, ladder->getBbox().Top - getBbox().Height));            
            isFalling = false;            
        }
                
    } 
    
    //Left Right - Up Down (ladder)
    if(!isFalling && !isCentring){
        if(input.Left)
            direction -= sf::Vector2f(speed.x, 0);
        
        if(input.Right)
            direction += sf::Vector2f(speed.x, 0);  
    }
    

    //Update X pos, and solve collisions
    if (direction.x != 0) {
        setPosition(sf::Vector2f(position.x + direction.x * seconds, position.y));
        
        
        Entity * b = world->getCollidingEnnemy(getBbox());
        if (b != NULL && b != this && b != world->getPlayer() && this != world->getPlayer()) {
            if (b->getPosition().x < getPosition().x)
                setPosition(getPosition() + sf::Vector2f(speed.x / 2 * seconds, 0));                    
            else 
               setPosition(getPosition() - sf::Vector2f(speed.x / 2 * seconds, 0));            
        }
        
        b = world->getCollidingSolid(getBbox());
        if (b != NULL) {
            if (direction.x < 0)
                setPosition(sf::Vector2f(b->getBbox().Left + b->getBbox().Width, position.y));
            else
                setPosition(sf::Vector2f(b->getBbox().Left - getBbox().Width, position.y));
        }
        
        
    }
    
    if(direction.x == 0 )
        alignToGridX();
    
    if(direction.y == 0)
        alignToGridY();        
}

void Character::setSpeed(sf::Vector2f speed) {
    this->speed = speed;
}

sf::Vector2f Character::getSpeed() {
    return speed;
}

void Character::align(sf::Vector2f pos) {
    if(!isFalling)
        setPosition(pos);
    else
        setPosition(sf::Vector2f(pos.x, getPosition().y));
}

void Character::alignToGridX() {
    setPosition( sf::Vector2f((int)(getCenter().x / Block::WIDTH) * Block::WIDTH + (Block::WIDTH - getBbox().Width) / 2, getPosition().y));
}

void Character::alignToGridY() {
    setPosition(sf::Vector2f(getPosition().x, (int)(getCenter().y / Block::HEIGHT) * Block::HEIGHT));
}
