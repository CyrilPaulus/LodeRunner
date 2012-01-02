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
#include "entity/Block.h"

class Game : public Screen{
public:
    Game();
    Game(const Game& orig);
    virtual ~Game();
    
    virtual int Run(sf::RenderWindow &app);
    
private:
    void Draw(sf::RenderTarget &app);
    void Update(unsigned int frametime);
    void HandleEvent(sf::Event event);
   
    //Event
    void OnKeyPressed(sf::Event event);
    void OnClose();
    
    bool running;
    ImageManager imgManager;
    Ticker* ticker;
    sf::Sprite *sprite;
    Block *block;
    int framecount;

};

#endif	/* GAME_H */

