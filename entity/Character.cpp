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
    speed = sf::Vector2f(100,100);
    isFalling = false;
    canFall = true;
    canRope = true;
    world = w;
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
    
    
    //Left Right - Up Down (ladder)
    if(!isFalling) {
        if(input.Left )
            direction -= sf::Vector2f(speed.x, 0);

        if(input.Right)
            direction += sf::Vector2f(speed.x, 0);  
    }

    if(input.Up && ladder) {
            direction = sf::Vector2f(0, 0);
            canFall = false;
            direction -= sf::Vector2f(0, speed.y);
            int deltaX = ladder->GetPosition().x + 0.5 *Block::WIDTH - (GetPosition().x + 0.5* bbox.x);
            if(deltaX > 0)
                direction += sf::Vector2f(speed.x, 0);                
            else if(deltaX < 0)
                direction -= sf::Vector2f(speed.x, 0);
        }
        
        if(input.Down && ladder) {
            direction = sf::Vector2f(0, 0);
            canFall = false;
            direction += sf::Vector2f(0, speed.y);
            int deltaX = ladder->GetPosition().x + 0.5 *Block::WIDTH - (GetPosition().x + 0.5* bbox.x);
            if(deltaX > 0)
                direction += sf::Vector2f(speed.x, 0);                
            else if(deltaX < 0)
                direction -= sf::Vector2f(speed.x, 0);
        }

    //Align to rope
    if ((rope && position.y >= rope->GetPosition().y && position.y <= rope->GetPosition().y + 10)) {
        if (canRope) {
            if (rope) {
                int deltaY = rope->GetPosition().y - GetPosition().y;
                if (abs(deltaY) < speed.y * seconds)
                    SetPosition(sf::Vector2f(position.x, rope->GetPosition().y));
                else if (deltaY > 0)
                    direction += sf::Vector2f(0, speed.y);
                else if (deltaY < 0)
                    direction -= sf::Vector2f(0, speed.y);

            }
            canFall = false;
            isFalling = false;
        }
    } else {
        canRope = true;
    }

    //Update X pos, and solve collisions
    if (direction.x != 0) {
        SetPosition(sf::Vector2f(position.x + direction.x * seconds, position.y));
        
        if(position.x < 0)
            SetPosition(sf::Vector2f(0, position.y));
        
        if(position.x + bbox.x >= world->GetSize().x)
            SetPosition(sf::Vector2f(world->GetSize().x - bbox.x, position.y));

        Block *b = world->GetCollidingSolid(GetBbox());
        if (b != NULL) {
            if (direction.x < 0)
                SetPosition(sf::Vector2f(b->GetBbox().Left + b->GetBbox().Width, position.y));
            else
                SetPosition(sf::Vector2f(b->GetBbox().Left - GetBbox().Width, position.y));
        }
    }
    
        
    if(input.Down && !canFall && rope) {
        canRope = false;
        canFall = true;  
    }    
    
    if(canFall) {
        isFalling = true;
        direction += sf::Vector2f(0, speed.y);        
    }     
    
    if(!ladder && (!rope || (position.x != rope->GetBbox().Top)))
        canFall = true;   
    
    if (direction.y != 0) {
        SetPosition(sf::Vector2f(position.x, position.y + direction.y * seconds));
        
        if(position.y < 0)
            SetPosition(sf::Vector2f(position.x, 0));
        
        if(position.y + bbox.y >= world->GetSize().y)
            SetPosition(sf::Vector2f(position.x, world->GetSize().y - bbox.y));

        Block *b = world->GetCollidingSolid(GetBbox());
        if (b != NULL) {
            if (direction.y < 0)
                SetPosition(sf::Vector2f(position.x, b->GetBbox().Top + b->GetBbox().Height));
            else {
                SetPosition(sf::Vector2f(position.x, b->GetBbox().Top - GetBbox().Height));
                isFalling = false;
            }
        }
        
        //Special case to walk on ladder
        ladder = world->GetCollidingLadder(GetBbox());
        if(ladder && direction.y > 0  && isFalling &&canFall && ladder->GetPosition().y > position.y) {
            if(!input.Down)
                SetPosition(sf::Vector2f(position.x, ladder->GetBbox().Top - GetBbox().Height));            
            isFalling = false;            
        }
                
    }
    
    if(direction.y == 0)
        isFalling = false;
   
  
}

void Character::SetSpeed(sf::Vector2f speed) {
    this->speed = speed;
}

sf::Vector2f Character::GetSpeed() {
    return speed;
}