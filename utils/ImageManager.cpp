/* 
 * File:   ImageManager.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 12:46 PM
 */

#include "ImageManager.h"
#include <iostream>

CImageManager::~CImageManager() {
    std::map<std::string, sf::Texture*>::iterator i;
    for(i = imageSet.begin(); i != imageSet.end(); i++) 
        delete i->second;
}

const sf::Texture *CImageManager::getImage(std::string name) {
    sf::Texture *value = imageSet[name];
    if(value != NULL)
        return value;
    
    value = new sf::Texture();
    if(!value->LoadFromFile("res/" + name + ".png")) {
        std::cerr << "Can't load image: " + name << std::endl;
        exit(-1);
    }
    
    imageSet[name] = value;
    return value;
}

