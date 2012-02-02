/* 
 * File:   Block.h
 * Author: cyril
 *
 * Created on January 2, 2012, 6:03 PM
 */

#ifndef BLOCK_H
#define	BLOCK_H

#include "Entity.h"

class Block : public Entity {
public:
    enum {EMPTY, WALL, CEMENT, LADDER, ROPE, FALSE, ENDLADDER};
    
    Block(int type);   
    
    void draw(sf::RenderTarget* rt);
    bool isSolid();
    bool isLadder();
    bool isRope();
    bool isAiSolid();
    void update(sf::Time frametime);
    
    int getType();
    
    void setActive(bool active);    
    
    static const int WIDTH = 36;
    static const int HEIGHT = 30;
    
private:
    
    bool active;
    static const char* file[];     
    sf::Time timer;
    int type;   
};

#endif	/* BLOCK_H */

