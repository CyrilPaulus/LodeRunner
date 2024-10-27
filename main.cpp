/* 
 * File:   main.cpp
 * Author: cyril
 *
 * Created on January 2, 2012, 12:02 PM
 */

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Game.h"
#include <iostream>


/*
 * 
 */
int main(int argc, char** argv) {
    //Init ImageManager
    ImageManager::getInstance();
    
    std::vector<Screen*> screens;       
    int screen = Screen::GAME;
    
    sf::RenderWindow app(sf::VideoMode(800,600), "LodeRunner");
    app.setMouseCursorVisible(false);
    
    Game game(&app);
    screens.push_back(&game);
    
    //Check arguments
    if(argc != 0) {
        for(int i = 0; i < argc; i++) {
            std::string arg = std::string(argv[i]);           
            if(arg.compare("-m") == 0 && i + 1 < argc) {
                std::cout << "Loading Map : " << argv[i + 1] << std::endl;
                game.loadMap(argv[i+1]);
            }
        }
    }    
    
    
    while(screen != Screen::EXIT) {
        screen = screens[screen]->run();
    }
    
    ImageManager::release();
    return EXIT_SUCCESS;
}

