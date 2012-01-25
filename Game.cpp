/* 
 * File:   Game.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 12:21 PM
 */

#include <iostream>
#include <sstream>
#include "Game.h"

#include "entity/Block.h"
#include "entity/World.h"


Game::Game(sf::RenderWindow *app) {
    running = false;
    ticker = new Ticker();
    ticker->setRate(50);
    
    world = new World();
    mapIndex = 0;
    this->app = app;    
    loadMap("res/map/map10");
    
    
}

Game::~Game() {
    delete(ticker);
    delete(world);
}

int Game::run() {
    running = true;
    sf::Event event;
    
    while(running) {
                
        //Manage event
        while(app->PollEvent(event)) {
            handleEvent(event);
        }
        
        if(ticker->tick())  
          update(ticker->getElapsedTime());
        
        //Draw screen
        draw(app);
        app->Display();
    }
    
    return Screen::EXIT;
}

void Game::update(sf::Time frametime) {
    Input input;
    input.Left = sf::Keyboard::IsKeyPressed(sf::Keyboard::Left);
    input.Right = sf::Keyboard::IsKeyPressed(sf::Keyboard::Right);
    input.Up = sf::Keyboard::IsKeyPressed(sf::Keyboard::Up);
    input.Down = sf::Keyboard::IsKeyPressed(sf::Keyboard::Down);
    input.LeftCarve = sf::Keyboard::IsKeyPressed(sf::Keyboard::A);
    input.RightCarve = sf::Keyboard::IsKeyPressed(sf::Keyboard::Z);
    
    int status = world->update(frametime, input);
    switch(status) {
        case World::WIN:
            nextMap();
            break;
        default:
            break;
    }
}

void Game::handleEvent(sf::Event event) {
    switch(event.Type) {
        case sf::Event::Closed:
            onClose();
            break;
        case sf::Event::KeyPressed:     
            onKeyPressed(event);
            break;
        default:
            break;
    }
}

void Game::onClose() {
    running = false;
}

void Game::onKeyPressed(sf::Event event) {
    switch(event.Key.Code) {
        case sf::Keyboard::Escape:
            onClose();
            break;
        case sf::Keyboard::N:
            nextMap();
            break;
        case sf::Keyboard::P:
            prevMap();
            break;
        default:
            break;
    }
}

void Game::draw(sf::RenderTarget *rt) {
    rt->Clear(sf::Color(150,150,150));  
    world->draw(rt);    
}

void Game::loadMap(std::string file) {
    std::cout << "Loading :" << file << std::endl;
    map = file;
    world->loadFromFile(file);
    app->SetSize(world->getSize().x, world->getSize().y);
    sf::View v = sf::View(sf::FloatRect(Block::WIDTH, Block::HEIGHT, world->getSize().x - 2*Block::WIDTH, world->getSize().y - 2*Block::HEIGHT));
    app->SetView(v);
}

void Game::nextMap() {    
    mapIndex++;    
    std::cout << mapIndex << std::endl;
    std::ostringstream nextMap;
    nextMap << "res/map/map" << mapIndex;    
    loadMap(nextMap.str());    
}

void Game::prevMap() {    
    if(mapIndex > 0) {
        mapIndex--;
        std::cout << mapIndex << std::endl;
        std::ostringstream nextMap;
         nextMap << "res/map/map" << mapIndex; 

        loadMap(nextMap.str());
    }
}
