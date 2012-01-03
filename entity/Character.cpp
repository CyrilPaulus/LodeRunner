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
    world = w;
}

void Character::Update(unsigned int frametime, Input input) {
    float seconds = frametime / (float)1000;
    sf::Vector2f direction = sf::Vector2f(0, 0);
    
    if(input.Left)
        direction -= sf::Vector2f(speed.x, 0);
    
    if(input.Right)
        direction += sf::Vector2f(speed.x, 0);
    
    if(input.Up)
        direction -= sf::Vector2f(0, speed.y);
    
    if(input.Down)
        direction += sf::Vector2f(0, speed.y);
    
    if(direction.x != 0){
      SetPosition(sf::Vector2f(position.x + direction.x * seconds, position.y));
      
      Block *b = world->GetCollidingSolid(GetBbox());
      if( b != NULL){
	if(direction.x < 0)
          SetPosition(sf::Vector2f(b->GetBbox().Left + b->GetBbox().Width, position.y));	  
	else
          SetPosition(sf::Vector2f(b->GetBbox().Left - GetBbox().Width, position.y));	 
      }
    }
    
    if(direction.y != 0){
      SetPosition(sf::Vector2f(position.x, position.y + direction.y * seconds));
      
      Block *b = world->GetCollidingSolid(GetBbox());
      if( b != NULL){
	if(direction.y < 0)
          SetPosition(sf::Vector2f(position.x, b->GetBbox().Top + b->GetBbox().Height));	  
	else
            SetPosition(sf::Vector2f(position.x, b->GetBbox().Top - GetBbox().Height));	 
      }
    }
   
  
}