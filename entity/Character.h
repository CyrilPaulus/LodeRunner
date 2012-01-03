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
#include "World.h"
class World;

class Character : public Entity {
public:
    Character(ImageManager* imgManager, World *world);
    void Update(unsigned int frametime, Input input);
    
private:
    sf::Vector2f speed; 
    bool moveX;
    bool moveY;
    bool isFalling;
    World *world;
};

#endif	/* CHARACTER_H */

