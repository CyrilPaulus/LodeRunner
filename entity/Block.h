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
    enum {WALL, CEMENT, LADDER, SLIDE};
    
    Block(ImageManager *imgManager, int type);
    
    void Update(unsigned int time);
    
private:
    static const char* file[];
    int type;
};

#endif	/* BLOCK_H */

