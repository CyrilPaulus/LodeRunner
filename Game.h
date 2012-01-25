/* 
 * File:   Game.h
 * Author: cyril
 *
 * Created on January 2, 2012, 12:21 PM
 */

#ifndef GAME_H
#define	GAME_H

#include "Screen.h"
#include "utils/ImageManager.h"
#include "utils/Ticker.h"

class World;

class Game : public Screen{
public:
    Game(sf::RenderWindow *app);
    virtual ~Game();
    
    void loadMap(std::string file);
    virtual int run();    
    
private:
    void draw(sf::RenderTarget *app);
    void handleEvent(sf::Event event);
    void update(sf::Time frametime);
    void nextMap();
    void prevMap();
    
    //Event
    void onKeyPressed(sf::Event event);
    void onClose();
    
    sf::RenderWindow *app;    
    std::string map;
    int mapIndex;
    bool running;
    Ticker* ticker;
    World* world;
};

#endif	/* GAME_H */

