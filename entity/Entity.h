/* 
 * File:   Entity.h
 * Author: cyril
 *
 * Created on January 2, 2012, 5:47 PM
 */

#include "../utils/ImageManager.h"

#ifndef ENTITY_H
#define	ENTITY_H

class Entity {
public:
    Entity(ImageManager *imgManager);
    virtual ~Entity();
    
    void Draw(sf::RenderTarget *rt);
    virtual void Update(unsigned int time) = 0;
    
    sf::Vector2f GetBbox();
    sf::Vector2f GetPosition(); 
    sf::Vector2f GetCenter();
    
    void SetPosition(sf::Vector2f pos);
    void SetBBox(sf::Vector2f bbox);
    void SetCenter(sf::Vector2f center);
    
protected:    
    sf::Sprite* image;
    sf::Vector2f position;
    sf::Vector2f center;
    sf::Vector2f bbox;

};

#endif	/* ENTITY_H */

