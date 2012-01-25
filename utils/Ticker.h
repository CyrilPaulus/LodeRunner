/* 
 * File:   Ticker.h
 * Author: cyril
 *
 * Created on January 2, 2012, 5:00 PM
 */

#ifndef TICKER_H
#define	TICKER_H

#include <SFML/System/Clock.hpp>

class Ticker {
public:
    Ticker();
    Ticker(sf::Time tickTime);
    
    bool tick();
    
    sf::Time getElapsedTime();
    
    void setRate(int tps);
    
private:
    sf::Clock clock;
    sf::Time tickTime;      
    sf::Time elapsedTime;
};

#endif	/* TICKER_H */

