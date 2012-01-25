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
    LoadMap("res/map/map10");
    
    
}

Game::~Game() {
    delete(ticker);
    delete(world);
}

int Game::Run() {
    running = true;
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

void Game::Update(sf::Time frametime) {
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
        case sf::Keyboard::N:
            NextMap();
            break;
        case sf::Keyboard::P:
            PrevMap();
            break;
        default:
            break;
    }
}

void Game::Draw(sf::RenderTarget *rt) {
    rt->Clear(sf::Color(150,150,150));  
    world->Draw(rt);    
}

void Game::LoadMap(std::string file) {
    std::cout << "Loading :" << file << std::endl;
    map = file;
    world->LoadFromFile(file);
    app->SetSize(world->GetSize().x, world->GetSize().y);
    sf::View v = sf::View(sf::FloatRect(Block::WIDTH, Block::HEIGHT, world->GetSize().x - 2*Block::WIDTH, world->GetSize().y - 2*Block::HEIGHT));
    app->SetView(v);
}

void Game::NextMap() {    
    mapIndex++;    
    std::cout << mapIndex << std::endl;
    std::ostringstream nextMap;
    nextMap << "res/map/map" << mapIndex;    
    LoadMap(nextMap.str());    
}

void Game::PrevMap() {    
    if(mapIndex > 0) {
        mapIndex--;
        std::cout << mapIndex << std::endl;
        std::ostringstream nextMap;
         nextMap << "res/map/map" << mapIndex; 

        LoadMap(nextMap.str());
    }
}
