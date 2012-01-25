/* 
 * File:   Goal.cpp
 * Author: cyril
 * 
 * Created on January 3, 2012, 6:07 PM
 */

#include "Goal.h"

Goal::Goal() : Entity() {
    image->SetTexture(*ImageManager::getInstance()->getImage("map/goal"));
    setBBox(sf::Vector2f(36, 30));
}

