/* 
 * File:   Game.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 12:21 PM
 */

#include <iostream>
#include "Game.h"

#include "entity/Block.h"
#include "entity/World.h"


Game::Game() {
    running = false;
    ticker = new Ticker();
    ticker->setRate(50);
    
    world = new World();
}

Game::~Game() {
    delete(ticker);
    delete(world);
}

int Game::Run(sf::RenderWindow *app) {
    running = true;
    world->LoadFromFile("res/map/map20");
    app->SetSize(world->GetSize().x, world->GetSize().y);
    sf::View v = sf::View(sf::FloatRect(Block::WIDTH, Block::HEIGHT, world->GetSize().x - 2*Block::WIDTH, world->GetSize().y - 2*Block::HEIGHT));
    app->SetView(v);
    
    sf::Event event;
    while(running) {
        
        //Manage event
        while(app->PollEvent(event)) {
            HandleEvent(event);
        }
        
        if(ticker->Tick()) 
          Update(ticker->getElapsedTime());
        
        //Draw screen
        Draw(app);
        app->Display();
    }
    
    return Screen::EXIT;
}

void Game::Update(unsigned int frametime) {
    Input input;
    input.Left = sf::Keyboard::IsKeyPressed(sf::Keyboard::Left);
    input.Right = sf::Keyboard::IsKeyPressed(sf::Keyboard::Right);
    input.Up = sf::Keyboard::IsKeyPressed(sf::Keyboard::Up);
    input.Down = sf::Keyboard::IsKeyPressed(sf::Keyboard::Down);
    input.LeftCarve = sf::Keyboard::IsKeyPressed(sf::Keyboard::A);
    input.RightCarve = sf::Keyboard::IsKeyPressed(sf::Keyboard::Z);
    
    world->Update(frametime, input);

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

void Game::Draw(sf::RenderTarget *rt) {
    rt->Clear(sf::Color(150,150,150));  
    world->Draw(rt);
   
    
}
