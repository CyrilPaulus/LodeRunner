/* 
 * File:   AiAgent.h
 * Author: cyril
 *
 * Created on January 4, 2012, 11:15 AM
 */

#ifndef AIAGENT_H
#define	AIAGENT_H

#include <list>
#include "../Input.h"
#include <SFML/System.hpp>


class World;
class Character;
class Block;


class AiAgent {
public:
    AiAgent(World *w, Character *c);    
    virtual ~AiAgent();
    
    Input update(sf::Time frametime);
    
private:
    std::list<Block*> computePath(int x0, int y0, int x1, int y1);
    
    Character* c;
    Block* current;
    std::list<Block*> path;
    sf::Time timer;
    World* world;
     
};

struct ANode {
 
  ANode* from;
  Block* block;
  int x, y;
  float g_score;
  float h_score;
  float f_score;
  
  ANode() {
    from = 0;
    block = 0;
    g_score = h_score = f_score = 0;
    x = y = -1;
  }

  bool operator==(const ANode& in) {
    return (block == in.block);
  }
  
  ANode& operator=(const ANode& rhs) {
      from = rhs.from;
      block = rhs.block;
      x = rhs.x;
      y = rhs.y;
      g_score = rhs.g_score;
      h_score = rhs.h_score;
      f_score = rhs.f_score;      
      return *this;
  }
  
  
};

#endif	/* AIAGENT_H */

