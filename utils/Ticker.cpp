/* 
 * File:   Ticker.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 5:00 PM
 */

#include <SFML/System/Time.hpp>

#include "Ticker.h"

Ticker::Ticker() {
    tickTime = sf::milliseconds(25);
    elapsedTime = sf::microseconds(0);
}

Ticker::Ticker(sf::Time ticktime) {
    this->tickTime = tickTime;
    elapsedTime = sf::microseconds(0);
}

bool Ticker::tick() {
  elapsedTime = clock.getElapsedTime();
  if(elapsedTime >= tickTime) {
    clock.restart();
    return true;
  }
  return false;
}

sf::Time Ticker::getElapsedTime() {
    return elapsedTime;
}

void Ticker::setRate(int tps) {
    tickTime = sf::milliseconds(1000 / tps);
}