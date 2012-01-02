/* 
 * File:   Entity.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 5:47 PM
 */

#include "Entity.h"

Entity::Entity(ImageManager *imgManager) {
    image = new sf::Sprite();
    position = sf::Vector2f(0,0);
    center = sf::Vector2f(0,0);
    bbox = sf::Vector2f(0,0);
}

Entity::~Entity() {
    delete(image);
}

void Entity::Draw(sf::RenderTarget* rt) {
    rt->Draw(*image);
}

sf::Vector2f Entity::GetPosition() {
    return position;
}

sf::Vector2f Entity::GetBbox() {
    return bbox;
}

sf::Vector2f Entity::GetCenter() {
    return center;
}

void Entity::SetBBox(sf::Vector2f bbox) {
    this->bbox = bbox;
}

void Entity::SetCenter(sf::Vector2f center) {
    this->center = center;
}

void Entity::SetPosition(sf::Vector2f position) {
    this->position = position;
    image->SetPosition(position);
}


