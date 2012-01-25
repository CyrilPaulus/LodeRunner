/* 
 * File:   AiManager.cpp
 * Author: cyril
 * 
 * Created on January 22, 2012, 5:13 PM
 */

#include "AiManager.h"
#include "AiAgent.h"

AiManager::AiManager(World* w) {
    world = w;
}

AiManager::~AiManager() {
    std::map<Character*, AiAgent*>::iterator it;
    for(it = agents.begin(); it != agents.end(); it++)
        delete((*it).second);
}

void AiManager::addAgent(Character* c) {
    AiAgent* a = new AiAgent(world, c);
    agents[c] = a;
}

Input AiManager::update(Character* c, sf::Time frametime) {
    return agents[c]->update(frametime);
}