/* 
 * File:   ImageManager.h
 * Author: cyril
 *
 * Created on January 2, 2012, 12:46 PM
 */

#ifndef IMAGEMANAGER_H
#define	IMAGEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "Singleton.h"

class CImageManager{
    
public:
    virtual ~CImageManager();
    const sf::Texture *get(std::string);
    
private:
    std::map<std::string, sf::Texture*> imageSet;

};

typedef Singleton<CImageManager> ImageManager;

#endif	/* IMAGEMANAGER_H */

