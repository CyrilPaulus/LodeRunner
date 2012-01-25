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
    
    int update(sf::Time frametime, Input in);
    void draw(sf::RenderTarget* rt);
    Block* getCollidingSolid(sf::FloatRect bbox);
    Block* getCollidingLadder(sf::FloatRect bbox);
    Block* getCollidingRope(sf::FloatRect bbox);
    Character* getCollidingEnnemy(sf::FloatRect bbox);
    
    sf::Vector2f getSize();
    
    Block* getBlock(int x, int y);
    std::list<Block*> getNeighbors(int x, int y);
    Character* getPlayer();
    
    
    void loadFromFile(std::string map);
private:
    int width;
    int height;
    bool completed;
    
    std::vector<Block*> blocks;
    std::vector<Goal*> goals;
    std::vector<Character*> enemies;
    Character* player;
    AiManager* ai;
    bool isUnderRope(int x, int y);
    void addBlock(int x, int y, int type);
    
    
    
    void clean();
    
    
    
};

#endif	/* WORLD_H */

