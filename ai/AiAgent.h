/* 
 * File:   AiAgent.h
 * Author: cyril
 *
 * Created on January 4, 2012, 11:15 AM
 */

#ifndef AIAGENT_H
#define	AIAGENT_H

#include <list>
#include "../entity/World.h"

class AiAgent {
public:
    AiAgent(World *w);
    std::list<Block*> ComputePath(int x0, int y0, int x1, int y1);   
    virtual ~AiAgent();
private:
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
    from = NULL;
    block = NULL;
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

