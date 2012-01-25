/* 
 * File:   Character.h
 * Author: cyril
 *
 * Created on January 2, 2012, 8:08 PM
 */

#ifndef CHARACTER_H
#define	CHARACTER_H
#include "Entity.h"
#include "../Input.h"

class Character;
class World;

class Character : public Entity {
public:
    Character(World *world);
    void update(sf::Time frametime, Input input);
    void setSpeed(sf::Vector2f speed);
    sf::Vector2f getSpeed();
    void align(sf::Vector2f pos);
    void alignToGridX();
    void alignToGridY();
    
private:
    sf::Vector2f speed; 
    sf::Vector2f direction;
    bool moveX;
    bool moveY;
    bool isFalling;
    bool isClimbing;
    bool isHanging;
    bool canFall;
    
    World *world;
};

#endif	/* CHARACTER_H */

