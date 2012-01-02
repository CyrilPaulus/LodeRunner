/* 
 * File:   main.cpp
 * Author: cyril
 *
 * Created on January 2, 2012, 12:02 PM
 */

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Game.h"


/*
 * 
 */
int main(int argc, char** argv) {
    std::vector<Screen*> screens;       
    int screen = Screen::GAME;
    
    sf::RenderWindow app(sf::VideoMode(800,600), "LodeRunner");
    app.ShowMouseCursor(false);
    
    Game game;
    screens.push_back(&game);
    
    while(screen != Screen::EXIT) {
        screen = screens[screen]->Run(app);
    }
    
    return EXIT_SUCCESS;
}

