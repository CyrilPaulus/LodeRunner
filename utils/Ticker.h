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
    Ticker(unsigned int tickTime);
    bool Tick();
    unsigned int getElapsedTime();
    void setRate(unsigned int rate);
    
private:
    sf::Clock clock;
    unsigned int tickTime;      
    unsigned int elapsedTime;
};

#endif	/* TICKER_H */

