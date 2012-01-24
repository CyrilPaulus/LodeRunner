/* 
 * File:   World.h
 * Author: cyril
 *
 * Created on January 2, 2012, 6:47 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include <vector>
#include <list>
#include <SFML/Graphics.hpp>
#include "../utils/ImageManager.h"
#include "Block.h"
#include "Goal.h"

class AiAgent;
#include "../ai/AiManager.h"
#include "Character.h"

class World {
public:
    World();
    virtual ~World();
    
    void Update(unsigned int frametime, Input in);
    void Draw(sf::RenderTarget* rt);
    Block* GetCollidingSolid(sf::FloatRect bbox);
    Block* GetCollidingLadder(sf::FloatRect bbox);
    Block* GetCollidingRope(sf::FloatRect bbox);
    Character* GetCollidingEnnemy(sf::FloatRect bbox);
    
    sf::Vector2f GetSize();
    
    Block* GetBlock(int x, int y);
    std::list<Block*> GetNeighbors(int x, int y);
    Character* GetPlayer();
    
    
    void LoadFromFile(char* filename);
private:
    int width;
    int height;
    bool completed;
    
    std::vector<Block*> blocks;
    std::vector<Goal*> goals;
    std::vector<Character*> enemies;
    Character* player;
    AiManager* ai;
    bool IsUnderRope(int x, int y);
    void PushBlock(int x, int y, int type);
    
    
    
    void Clean();
    
    
    
};

#endif	/* WORLD_H */

