/* 
 * File:   AiManager.h
 * Author: cyril
 *
 * Created on January 22, 2012, 5:13 PM
 */

#ifndef AIMANAGER_H
#define	AIMANAGER_H
#include <map>
#include "SFML/System.hpp"
class World;
class Character;
class Input;
class AiAgent;

class AiManager {
public:
    AiManager(World* w);
    virtual ~AiManager();
  
    void addAgent(Character *c);
    Input update(Character *c, sf::Time frametime);
    
private:
    std::map<Character*, AiAgent*> agents;
    World *world;
};

#endif	/* AIMANAGER_H */

