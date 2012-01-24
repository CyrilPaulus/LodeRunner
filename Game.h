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
    Game();
    Game(const Game& orig);
    virtual ~Game();
    
    virtual int Run(sf::RenderWindow *app);
    
private:
    void Draw(sf::RenderTarget *app);
    void Update(unsigned int frametime);
    void HandleEvent(sf::Event event);
   
    //Event
    void OnKeyPressed(sf::Event event);
    void OnClose();
    
    bool running;
    Ticker* ticker;
    
    World* world;

};

#endif	/* GAME_H */

