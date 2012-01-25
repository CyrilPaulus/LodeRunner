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
    
    void draw(sf::RenderTarget* rt);
    void loadFromFile(std::string map);
    int update(sf::Time frametime, Input in);
    
    Block* getBlock(int x, int y);
    Block* getCollidingSolid(sf::FloatRect bbox);
    Block* getCollidingLadder(sf::FloatRect bbox);
    Block* getCollidingRope(sf::FloatRect bbox);
    Character* getCollidingEnnemy(sf::FloatRect bbox);
    std::list<Block*> getNeighbors(int x, int y);
    Character* getPlayer();
    sf::Vector2f getSize();    
    
private:
       
    void addBlock(int x, int y, int type);
    void clean();
    bool isUnderRope(int x, int y);   
    
    int width;
    int height;
    bool completed;
    
    AiManager* ai;
    Character* player;
    std::vector<Block*> blocks;
    std::vector<Goal*> goals;
    std::vector<Character*> enemies;  
    
};

#endif	/* WORLD_H */

