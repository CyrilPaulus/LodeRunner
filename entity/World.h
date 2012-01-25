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

#include "../Input.h"

class AiManager;
class Block;
class Goal;
class Character;

class World {
public:
    enum {NOTHING, WIN, DEAD};
    
    World();
    virtual ~World();
    
    int Update(sf::Time frametime, Input in);
    void Draw(sf::RenderTarget* rt);
    Block* GetCollidingSolid(sf::FloatRect bbox);
    Block* GetCollidingLadder(sf::FloatRect bbox);
    Block* GetCollidingRope(sf::FloatRect bbox);
    Character* GetCollidingEnnemy(sf::FloatRect bbox);
    
    sf::Vector2f GetSize();
    
    Block* GetBlock(int x, int y);
    std::list<Block*> GetNeighbors(int x, int y);
    Character* GetPlayer();
    
    
    void LoadFromFile(std::string map);
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

