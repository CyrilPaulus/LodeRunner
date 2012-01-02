/* 
 * File:   Screen.h
 * Author: cyril
 *
 * Created on January 2, 2012, 12:03 PM
 */

#ifndef SCREEN_H
#define	SCREEN_H

#include <SFML/Graphics.hpp>

class Screen {
public:
    enum {EXIT = -1, GAME};
    virtual int Run (sf::RenderWindow &App) = 0;
    
private:

};

#endif	/* SCREEN_H */

