/* 
 * File:   World.h
 * Author: cyril
 *
 * Created on January 2, 2012, 6:47 PM
 */

#ifndef WORLD_H
#define	WORLD_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "../utils/ImageManager.h"
#include "Block.h"


class World {
public:
    World(ImageManager *imgManager);
    
    void Update(unsigned int frametime);
    void Draw(sf::RenderTarget* rt);
    
    virtual ~World();
    
    void LoadFromFile(char* filename);
private:
    int width;
    int height;
    
    ImageManager *imgManager;
    std::vector<Block*> blocks;
    
};

#endif	/* WORLD_H */

