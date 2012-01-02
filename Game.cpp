/* 
 * File:   Game.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 12:21 PM
 */

#include <iostream>
#include "Game.h"


Game::Game() {
    running = false;
    ticker = new Ticker();
    ticker->setRate(50);
    
    sprite = new sf::Sprite();
    sprite->SetTexture(*(imgManager.get("player")));
    framecount = 0;
}

Game::~Game() {
    delete(ticker);
    delete(sprite);
}

int Game::Run(sf::RenderWindow& app) {
    running = true;
    
    sf::Event event;
    while(running) {
        
        //Manage event
        while(app.PollEvent(event)) {
            HandleEvent(event);
        }
        
        if(ticker->Tick()) 
          Update(ticker->getElapsedTime());
        
        //Draw screen
        Draw(app);
        app.Display();
    }
    
    return Screen::EXIT;
}

void Game::Update(unsigned int frametime) {
    framecount++;
    std::cout << framecount << std::endl;
}

void Game::HandleEvent(sf::Event event) {
    switch(event.Type) {
        case sf::Event::Closed:
            OnClose();
            break;
        case sf::Event::KeyPressed:     
            OnKeyPressed(event);
            break;
        default:
            break;
    }
}

void Game::OnClose() {
    running = false;
}

void Game::OnKeyPressed(sf::Event event) {
    switch(event.Key.Code) {
        case sf::Keyboard::Escape:
            OnClose();
            break;
        default:
            break;
    }
}

void Game::Draw(sf::RenderTarget &target) {
    target.Clear(sf::Color(150,150,150));
    
    
    target.Draw(*sprite);    
    
}