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
    
    virtual int Run();
    void LoadMap(std::string file);
    
    
private:
    void Draw(sf::RenderTarget *app);
    void Update(sf::Time frametime);
    void HandleEvent(sf::Event event);
    sf::RenderWindow *app;
   
    //Event
    void OnKeyPressed(sf::Event event);
    void OnClose();
    
    bool running;
    Ticker* ticker;
    
    World* world;
    std::string map;
    int mapIndex;
    
    void NextMap();
    void PrevMap();

};

#endif	/* GAME_H */

