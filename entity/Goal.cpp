/* 
 * File:   Goal.cpp
 * Author: cyril
 * 
 * Created on January 3, 2012, 6:07 PM
 */

#include "Goal.h"

Goal::Goal() : Entity() {
    image->SetTexture(*ImageManagerSingleton::GetInstance()->get("map/goal"));
    SetBBox(sf::Vector2f(36, 30));
}

