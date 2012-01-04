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
#include "Character.h"
#include "../ai/AiAgent.h"

class AiAgent;
class Character;


class World {
public:
    World(ImageManager *imgManager);
    virtual ~World();
    
    void Update(unsigned int frametime, Input in);
    void Draw(sf::RenderTarget* rt);
    Block* GetCollidingSolid(sf::FloatRect bbox);
    Block* GetCollidingLadder(sf::FloatRect bbox);
    Block* GetCollidingRope(sf::FloatRect bbox);
    sf::Vector2f GetSize();
    
    Block* GetBlock(int x, int y);
    std::list<Block*> GetNeighbors(int x, int y);
    
    
    void LoadFromFile(char* filename);
private:
    int width;
    int height;
    bool completed;
    
    ImageManager *imgManager;
    std::vector<Block*> blocks;
    std::vector<Goal*> goals;
    std::vector<Character*> enemies;
    Character* player;
    AiAgent* ai;
    bool IsUnderRope(int x, int y);
    
    
    
    void Clean();
    
    
    
};

#endif	/* WORLD_H */

