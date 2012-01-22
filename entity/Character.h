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

#include "World.h"


class Character : public Entity {
public:
    Character(World *world);
    void Update(unsigned int frametime, Input input);
    void SetSpeed(sf::Vector2f speed);
private:
    sf::Vector2f speed; 
    bool moveX;
    bool moveY;
    bool isFalling;
    bool canFall;
    bool canRope;
    World *world;
};

#endif	/* CHARACTER_H */

