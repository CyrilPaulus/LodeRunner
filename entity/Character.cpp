/* 
 * File:   Character.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 8:08 PM
 */

#include "Character.h"
#include "Block.h"
#include "World.h"
Character::Character(World *w) : Entity() {
    image->SetTexture(*ImageManager::getInstance()->get("them"));
    SetBBox(sf::Vector2f(24, 30));
    speed = sf::Vector2f(250,150);
    isFalling = false;
    canFall = true;
    isHanging = false;
    isClimbing = false;
    world = w;
    direction = sf::Vector2f(0, 0);
}

void Character::Update(unsigned int frametime, Input input) {
    
    int x0 = position.x / Block::WIDTH;
    int y0 = position.y / Block::HEIGHT;
    float seconds = frametime / (float)1000;
    
    //Carve
    if(input.LeftCarve) {
        Block* b = world->GetBlock(x0 - 1, y0 + 1);
        Block* c = world->GetBlock(x0 - 1, y0 );
        if(b && b->GetType() == Block::WALL && !c->IsSolid() && !c->IsLadder() && !c->IsRope())
            b->SetActive(false);
    }
    
    if(input.RightCarve) {
        Block* b = world->GetBlock(x0 + 1, y0 + 1);
        Block* c = world->GetBlock(x0 + 1, y0);
        if(b && b->GetType() == Block::WALL && !c->IsSolid() && !c->IsLadder() && !c->IsRope())
            b->SetActive(false);
    }
    
    sf::Vector2f direction = sf::Vector2f(0, 0);
    Block* rope = world->GetCollidingRope(GetBbox());
    Block* ladder = world->GetCollidingLadder(GetBbox());

    bool isCentring = false;
    if ((input.Up || input.Down || isFalling) && ladder && ((abs(GetCenter().x - ladder->GetCenter().x) < 4))) {

        isClimbing = true;
        if (input.Up)
            direction -= sf::Vector2f(0, speed.y);
        else
            direction += sf::Vector2f(0, speed.y);
        
        isCentring = true;
        
        AlignToGridX();
    } else if (!ladder) {
        isClimbing = false;
    }    

    //Align to rope
    if (rope && (input.Left || input.Right || isFalling) && !(input.Down)) {
        isHanging = true;

        int deltaY = rope->GetPosition().y - GetPosition().y;
        if (abs(deltaY) < 4)
            SetPosition(sf::Vector2f(position.x, rope->GetPosition().y));
    }
    
    
    if (!rope || input.Down || rope->GetPosition().y != GetPosition().y)
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
        SetPosition(sf::Vector2f(position.x, position.y + direction.y * seconds));
              
        Entity *b = world->GetCollidingSolid(GetBbox());
        if (b != NULL) {
            if (direction.y < 0)
                SetPosition(sf::Vector2f(position.x, b->GetBbox().Top + b->GetBbox().Height));
            else {
                SetPosition(sf::Vector2f(position.x, b->GetBbox().Top - GetBbox().Height));
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
        ladder = world->GetCollidingLadder(GetBbox());
        if(ladder && direction.y > 0  && isFalling && ladder->GetPosition().y > position.y) {
            if(!input.Down)
                SetPosition(sf::Vector2f(position.x, ladder->GetBbox().Top - GetBbox().Height));            
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
        SetPosition(sf::Vector2f(position.x + direction.x * seconds, position.y));
        
        
        Entity * b = world->GetCollidingEnnemy(GetBbox());
        if (b != NULL && b != this && b != world->GetPlayer() && this != world->GetPlayer()) {
            if (b->GetPosition().x < GetPosition().x)
                SetPosition(GetPosition() + sf::Vector2f(speed.x / 2 * seconds, 0));                    
            else 
               SetPosition(GetPosition() - sf::Vector2f(speed.x / 2 * seconds, 0));            
        }
        
        b = world->GetCollidingSolid(GetBbox());
        if (b != NULL) {
            if (direction.x < 0)
                SetPosition(sf::Vector2f(b->GetBbox().Left + b->GetBbox().Width, position.y));
            else
                SetPosition(sf::Vector2f(b->GetBbox().Left - GetBbox().Width, position.y));
        }
        
        
    }
    
    if(direction.x == 0 )
        AlignToGridX();
    
    if(direction.y == 0)
        AlignToGridY();        
}

void Character::SetSpeed(sf::Vector2f speed) {
    this->speed = speed;
}

sf::Vector2f Character::GetSpeed() {
    return speed;
}

void Character::Align(sf::Vector2f pos) {
    if(!isFalling)
        SetPosition(pos);
    else
        SetPosition(sf::Vector2f(pos.x, GetPosition().y));
}

void Character::AlignToGridX() {
    SetPosition( sf::Vector2f((int)(GetCenter().x / Block::WIDTH) * Block::WIDTH + (Block::WIDTH - GetBbox().Width) / 2, GetPosition().y));
}

void Character::AlignToGridY() {
    SetPosition(sf::Vector2f(GetPosition().x, (int)(GetCenter().y / Block::HEIGHT) * Block::HEIGHT));
}