/* 
 * File:   Ticker.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 5:00 PM
 */

#include <SFML/System/Time.hpp>

#include "Ticker.h"

Ticker::Ticker() {
    tickTime = sf::Milliseconds(25);
    elapsedTime = sf::Microseconds(0);
}

Ticker::Ticker(sf::Time ticktime) {
    this->tickTime = tickTime;
    elapsedTime = sf::Microseconds(0);
}

bool Ticker::Tick() {
  elapsedTime = clock.GetElapsedTime();
  if(elapsedTime >= tickTime) {
    clock.Restart();  
    return true;
  }
  return false;
}

sf::Time Ticker::getElapsedTime() {
    return elapsedTime;
}

void Ticker::setRate(int tps) {
    tickTime = sf::Milliseconds(1000 / tps);
}