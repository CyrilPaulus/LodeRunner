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

AiManager::AiManager(const AiManager& orig) {
}

AiManager::~AiManager() {
    std::map<Character*, AiAgent*>::iterator it;
    for(it = agents.begin(); it != agents.end(); it++)
        delete((*it).second);
}

void AiManager::AddAgent(Character* c) {
    AiAgent* a = new AiAgent(world, c);
    agents[c] = a;
}

Input AiManager::Update(Character* c, sf::Time frametime) {
    return agents[c]->Update(frametime);
}