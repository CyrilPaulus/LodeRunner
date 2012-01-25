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
    Entity();
    virtual ~Entity();
    
    void draw(sf::RenderTarget *rt);
    
    sf::FloatRect getBbox();
    sf::Vector2f getPosition(); 
    sf::Vector2f getCenter();
    
    void setBBox(sf::Vector2f bbox);
    void setCenter(sf::Vector2f center);
    void setColor(sf::Color color);
    void setPosition(sf::Vector2f pos);    
    
protected:    
    sf::Sprite* image;
    sf::Vector2f position;
    sf::Vector2f bbox;

};

#endif	/* ENTITY_H */

