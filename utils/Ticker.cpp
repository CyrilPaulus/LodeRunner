/* 
 * File:   Ticker.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 5:00 PM
 */

#include "Ticker.h"

Ticker::Ticker() {
    tickTime = 25;
    elapsedTime = 0;
}

Ticker::Ticker(unsigned int tickTime) {
    this->tickTime = tickTime;
    elapsedTime = 0;
}

bool Ticker::Tick() {
    elapsedTime = clock.GetElapsedTime();
    if(elapsedTime >= tickTime) {
        clock.Reset();  
        return true;
    }
    return false;
}

unsigned int Ticker::getElapsedTime() {
    return elapsedTime;
}

void Ticker::setRate(unsigned int rate) {
    tickTime = 1000 / rate;
}




