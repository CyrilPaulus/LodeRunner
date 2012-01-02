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

class ImageManager {
public:
    virtual ~ImageManager();
    const sf::Texture *get(std::string);
    
private:
    std::map<std::string, sf::Texture*> imageSet;

};

#endif	/* IMAGEMANAGER_H */

