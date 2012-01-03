/* 
 * File:   World.h
 * Author: cyril
 *
 * Created on January 2, 2012, 6:47 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "../utils/ImageManager.h"
#include "Block.h"
#include "Character.h"

class Character;

class World {
public:
    World(ImageManager *imgManager);
    
    void Update(unsigned int frametime, Input in);
    void Draw(sf::RenderTarget* rt);
    Block* GetCollidingSolid(sf::FloatRect bbox);
    Block* GetCollidingLadder(sf::FloatRect bbox);
    Block* GetCollidingRope(sf::FloatRect bbox);
    sf::Vector2f GetSize();
    
    virtual ~World();
    
    void LoadFromFile(char* filename);
private:
    int width;
    int height;
    
    ImageManager *imgManager;
    std::vector<Block*> blocks;
    Character* player;
    
    
    
};

#endif	/* WORLD_H */

