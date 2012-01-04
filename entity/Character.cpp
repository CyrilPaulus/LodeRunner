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
    
    int x0 = position.x / Block::WIDTH;
    int y0 = position.y / Block::HEIGHT;
    float seconds = frametime / (float)1000;
    
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
    
    if(!isFalling) {
        if(input.Left && !input.Up && !input.Down)
            direction -= sf::Vector2f(speed.x, 0);

        if(input.Right && !input.Up && !input.Down)
            direction += sf::Vector2f(speed.x, 0);
        
        if(input.Up && ladder) {
            canFall = false;
            direction -= sf::Vector2f(0, speed.y);
            int deltaX = ladder->GetPosition().x + 0.5 *Block::WIDTH - (GetPosition().x + 0.5* bbox.x);
            if(deltaX > 0)
                direction += sf::Vector2f(speed.x, 0);                
            else if(deltaX < 0)
                direction -= sf::Vector2f(speed.x, 0);
        }
        
        if(input.Down && ladder) {
            canFall = false;
            direction += sf::Vector2f(0, speed.y);
            int deltaX = ladder->GetPosition().x + 0.5 *Block::WIDTH - (GetPosition().x + 0.5* bbox.x);
            if(deltaX > 0)
                direction += sf::Vector2f(speed.x, 0);                
            else if(deltaX < 0)
                direction -= sf::Vector2f(speed.x, 0);
        }
      
    }
    

    if ((rope && GetBbox().Top >= rope->GetBbox().Top && GetBbox().Top <= rope->GetBbox().Top + 3 && !input.Down) || ladder) {
        if (rope && !ladder) {
            int deltaY = rope->GetPosition().y - GetPosition().y;
            if(deltaY < 0)
                direction += sf::Vector2f(0, speed.y);
             else if(deltaY > 0)
                 direction -= sf::Vector2f(0, speed.y);            
        }
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
        if(ladder != NULL && direction.y > 0 && isFalling && canFall && ladder->GetPosition().y > position.y) {
            if(!input.Down)
                SetPosition(sf::Vector2f(position.x, ladder->GetBbox().Top - GetBbox().Height));            
            isFalling = false;            
        }
        
        
    }  
   
  
}

void Character::SetSpeed(sf::Vector2f speed) {
    this->speed = speed;
}