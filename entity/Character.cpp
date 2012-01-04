/* 
 * File:   Character.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 8:08 PM
 */

#include "Character.h"
#include "Block.h"

Character::Character(ImageManager* imgManager, World *w) : Entity(imgManager) {
    image->SetTexture(*imgManager->get("them"));
    SetBBox(sf::Vector2f(24, 30));
    speed = sf::Vector2f(100,100);
    isFalling = false;
    canFall = true;
    world = w;
}

void Character::Update(unsigned int frametime, Input input) {
    float seconds = frametime / (float)1000;
    sf::Vector2f direction = sf::Vector2f(0, 0);
    Block* rope = world->GetCollidingRope(GetBbox());
    Block* ladder = world->GetCollidingLadder(GetBbox());
    
    if(!isFalling) {
        if(input.Left)
            direction -= sf::Vector2f(speed.x, 0);

        if(input.Right)
            direction += sf::Vector2f(speed.x, 0);
        
        if(input.Up && ladder) {
            canFall = false;
            direction -= sf::Vector2f(0, speed.y);
            SetPosition(sf::Vector2f(ladder->GetPosition().x + 0.5 * (Block::WIDTH - bbox.x) ,GetPosition().y ));            
        }
        
        if(input.Down && ladder) {
            canFall = false;
            direction += sf::Vector2f(0, speed.y);
            SetPosition(sf::Vector2f(ladder->GetPosition().x + 0.5 * (Block::WIDTH - bbox.x) ,GetPosition().y ));
        }
      
    }
    

    if ((rope && GetBbox().Top >= rope->GetBbox().Top && GetBbox().Top <= rope->GetBbox().Top + 3 && !input.Down) || ladder) {
        if (rope)
            SetPosition(sf::Vector2f(GetPosition().x, rope->GetPosition().y));
        canFall = false;
        isFalling = false;
    }

    if(input.Down && !canFall && rope)
            canFall = true;   
    
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
            SetPosition(sf::Vector2f(0, world->GetSize().y - bbox.y));

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
        if(ladder != NULL && direction.y > 0 && isFalling && canFall && ladder->GetPosition().y > position.y) {
            if(!input.Down)
                SetPosition(sf::Vector2f(position.x, ladder->GetBbox().Top - GetBbox().Height));            
            isFalling = false;            
        }
        
        
    }  
   
  
}