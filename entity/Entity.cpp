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

void Entity::Draw(sf::RenderTarget* rt) {
    rt->Draw(*image);
}

void Entity::SetColor(sf::Color color) {
    image->SetColor(color);
}

sf::Vector2f Entity::GetPosition() {
    return position;
}

sf::FloatRect Entity::GetBbox() {
    return sf::FloatRect(position, bbox);
}

sf::Vector2f Entity::GetCenter() {
    return position + sf::Vector2f(bbox.x / 2, bbox.y / 2);
}

void Entity::SetBBox(sf::Vector2f bbox) {
    this->bbox = bbox;
}

void Entity::SetPosition(sf::Vector2f position) {
    this->position = position;
    image->SetPosition(position);
}



