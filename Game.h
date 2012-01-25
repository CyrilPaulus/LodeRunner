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
    Game(const Game& orig);
    virtual ~Game();
    
    virtual int run();
    void loadMap(std::string file);
    
    
private:
    void draw(sf::RenderTarget *app);
    void update(sf::Time frametime);
    void handleEvent(sf::Event event);
    sf::RenderWindow *app;
   
    //Event
    void onKeyPressed(sf::Event event);
    void onClose();
    
    bool running;
    Ticker* ticker;
    
    World* world;
    std::string map;
    int mapIndex;
    
    void nextMap();
    void prevMap();

};

#endif	/* GAME_H */

