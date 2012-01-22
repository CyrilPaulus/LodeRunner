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
    static const int WIDTH = 36;
    static const int HEIGHT = 30;
    
    Block(int type);
    
    void Update(unsigned int time);
    void Draw(sf::RenderTarget* rt);
    bool IsSolid();
    bool IsLadder();
    bool IsRope();
    void SetActive(bool active);
    int GetType();
    
private:
    
    static const char* file[];
    int type;
    bool active;
    float timer;
};

#endif	/* BLOCK_H */

