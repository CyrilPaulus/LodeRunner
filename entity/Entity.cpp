/* 
 * File:   Entity.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 5:47 PM
 */

#include "Entity.h"

Entity::Entity() {
    image = new sf::Sprite();
    position = sf::Vector2f(0,0);
    bbox = sf::Vector2f(0,0);
}

Entity::~Entity() {
    delete(image);
}

void Entity::draw(sf::RenderTarget* rt) {
    rt->draw(*image);
}

void Entity::setColor(sf::Color color) {
    image->setColor(color);
}

sf::Vector2f Entity::getPosition() {
    return position;
}

sf::FloatRect Entity::getBbox() {
    return sf::FloatRect(position, bbox);
}

sf::Vector2f Entity::getCenter() {
    return position + sf::Vector2f(bbox.x / 2, bbox.y / 2);
}

void Entity::setBBox(sf::Vector2f bbox) {
    this->bbox = bbox;
}

void Entity::setPosition(sf::Vector2f position) {
    this->position = position;
    image->setPosition(position);
}



