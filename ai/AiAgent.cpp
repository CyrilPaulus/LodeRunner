/* 
 * File:   AiAgent.cpp
 * Author: cyril
 * 
 * Created on January 4, 2012, 11:15 AM
 */


#include "AiAgent.h"
#include <set>
#include <iostream>
#include <SFML/System/Time.hpp>

#include "../entity/World.h"
#include "../entity/Character.h"
#include "../entity/Block.h"

int distM(int x0, int y0, int x1, int y1) {
    return abs(x0 - x1) + abs (y0 - y1);
}

AiAgent::AiAgent(World* w, Character *c) {
    world = w;
    this->c = c;
    current = NULL;
    timer = sf::Seconds(0);
}

AiAgent::~AiAgent() {
}

struct comp {
    bool operator()(const ANode *a, const ANode *b) {
        return (a->y * Block::WIDTH + a->x) < (b->y * Block::WIDTH + b->x);
    }
};

std::list<Block*> AiAgent::computePath(int x0, int y0, int x1, int y1) {
    std::list<Block*> result;
    
    std::set<ANode*, comp> closedset;
    std::set<ANode*, comp> openset;
    
    ANode* start = new ANode();
    start->block = world->getBlock(x0, y0);
    start->x = x0;
    start->y = y0;
    start->g_score = 0;
    start->f_score = distM(x0, y0, x1, y1);
    start->h_score = start->g_score + start->f_score;
    
    openset.insert(start);
    
    while(!openset.empty()) {
        ANode* x = NULL;
        int f_min = -1;
        
        std::set<ANode*>::iterator it;
        for(it = openset.begin(); it != openset.end(); it++) {
            
            if(f_min == -1 || (*it)->f_score < f_min){
                x = *it;
                f_min = x->f_score;
                
            }
        }
        
       if(x->x == x1 && x->y == y1) {
            while(x->x != x0 || x->y != y0) {
                result.push_front(x->block);
                x = x->from;
            }
            break;
        }            
        
        openset.erase(x);
        closedset.insert(x);
        
        std::list<Block*> neighbours = world->getNeighbors(x->x, x->y);
        std::list<Block*>::iterator bi;
        for(bi = neighbours.begin(); bi != neighbours.end(); bi++ ) {
            ANode* y = new ANode();
            y->block = *bi;
            y->from = x;
            y->x = (*bi)->getPosition().x / Block::WIDTH;
            y->y = (*bi)->getPosition().y / Block::HEIGHT;
            y->g_score = x->g_score + 1;
            y->h_score = distM(y->x, y->y, x1, y1);
            y->f_score = y->g_score + y->h_score;
            
            if(closedset.find(y) != closedset.end()) {
               delete(y);
               continue;
            }
                     
            std::set<ANode*>::iterator fn = openset.find(y);
            if(fn == openset.end()) {
                openset.insert(y);
               
            }else if (y->g_score < (*fn)->g_score) {          
                openset.erase(*fn);
                openset.insert(y);
            } else {
                delete(y);
            }            
        }
    }
    std::set<ANode*>::iterator it;
    for(it = closedset.begin(); it != closedset.end(); it++)        
        delete(*it);
    
    for(it = openset.begin(); it != openset.end(); it++)
        delete(*it);
    
    return result;
}

Input AiAgent::update(sf::Time frametime) {
    
    timer += frametime;
    
    if(timer >= sf::Seconds(0.5)) {
        timer = sf::Seconds(0);
        path.clear();
    }    
    
    Input rtn;    
    
    if(path.empty()) {      

     int x0 = c->getPosition().x / Block::WIDTH;
        int y0 = c->getPosition().y / Block::HEIGHT;

        int x1 = world->getPlayer()->getPosition().x / Block::WIDTH;
        int y1 = world->getPlayer()->getPosition().y / Block::HEIGHT;
        
        path = computePath(x0, y0, x1, y1);
        
    }   
    
    //FUCK YEAH
  /* for(std::list<Block*>::iterator it = path.begin(); it != path.end(); it++){
       long color = reinterpret_cast<long>(this);       
        (*it)->setColor(sf::Color(color, color >> 8, color >> 16));
    }*/
    
    if(!path.empty()) {
        Block* first = path.front();
        
        if(abs(first->getPosition().y - c->getPosition().y) <= c->getSpeed().y * frametime.AsSeconds())
            c->align(sf::Vector2f(c->getPosition().x, first->getPosition().y));            
        
        
        if(first->getPosition().x + 0.5 * Block::WIDTH < c->getPosition().x + 0.5 * c->getBbox().Width)
            rtn.Left = true;        
        
        if(first->getPosition().x + 0.5 * Block::WIDTH > c->getPosition().x + 0.5 * c->getBbox().Width)
            rtn.Right = true;     
        
        if(first->getPosition().y + 0.5 * Block::HEIGHT < c->getPosition().y + 0.5 * c->getBbox().Height)
            rtn.Up = true;
        
        if(first->getPosition().y + 0.5 * Block::HEIGHT > c->getPosition().y + 0.5 * c->getBbox().Height)
            rtn.Down = true; 
   
        sf::Vector2f dist = c->getCenter() - first->getCenter();
            
        if (dist.x * dist.x + dist.y * dist.y <= 64)           
            path.pop_front();  
        
    }
    
    return rtn;
}
