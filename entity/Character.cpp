/* 
 * File:   Character.cpp
 * Author: cyril
 * 
 * Created on January 2, 2012, 8:08 PM
 */

#include "Character.h"
#include "Block.h"
#include "World.h"
#include <math.h>
#include <iostream>

Character::Character(World *w) : Entity() {
    image->setTexture(*ImageManager::getInstance()->getImage("them"));
    setBBox(sf::Vector2f(24, 30));
    speed = sf::Vector2f(250, 150);
    isFalling = false;
    canFall = true;
    canMove = true;
    isHanging = false;
    isClimbing = false;
    world = w;
    direction = sf::Vector2f(0, 0);
    origin = sf::Vector2f(0,0);  
}

void Character::update(sf::Time frametime, Input input) {

    if(!canMove)
        return;
    
    int x0 = position.x / Block::WIDTH;
    int y0 = position.y / Block::HEIGHT;
    float seconds = frametime.asSeconds();

    //Carve

    if (input.LeftCarve && !lastInput.LeftCarve) {
        Block* b = world->getBlock(x0 - 1, y0 + 1);
        Block* c = world->getBlock(x0 - 1, y0);
        if (b && b->getType() == Block::WALL && !c->isSolid() && !c->isLadder() && !c->isRope())
            b->setActive(false);
    }

    if (input.RightCarve && !lastInput.RightCarve) {
        Block* b = world->getBlock(x0 + 1, y0 + 1);
        Block* c = world->getBlock(x0 + 1, y0);
        if (b && b->getType() == Block::WALL && !c->isSolid() && !c->isLadder() && !c->isRope())
            b->setActive(false);
    }
        lastInput = input;
    sf::Vector2f direction = sf::Vector2f(0, 0);
    Block* rope = world->getCollidingRope(getBbox());
    Block* ladder = world->getCollidingLadder(getBbox());

    bool isCentring = false;
    if (ladder) {
        
        isClimbing = true;

        if (input.Up)
            direction -= sf::Vector2f(0, speed.y);
        else if (input.Down)
            direction += sf::Vector2f(0, speed.y);

        if (input.Up || input.Down) {
            if (fabs(getCenter().x - ladder->getCenter().x) < speed.y * seconds)
                alignToGridX();
            else if (getCenter().x < ladder->getCenter().x)
                direction.x += speed.x;
            else if (getCenter().x > ladder->getCenter().x)
                direction.x -= speed.x;

            isCentring = true;
        }
        
    } else {
        isClimbing = false;
    }

    //Align to rope
    if (rope && (input.Left || input.Right || isFalling) && !(input.Down)) {
        isHanging = true;

        int deltaY = rope->getPosition().y - getPosition().y;
        if (abs(deltaY) < 4)
            setPosition(sf::Vector2f(position.x, rope->getPosition().y));
    }

    if (!rope || input.Down || rope->getPosition().y != getPosition().y)
        isHanging = false;

    if (isClimbing && isHanging)
        isClimbing = false;

    if (!isHanging && !isClimbing)
        isFalling = true;
    else
        isFalling = false;

    if (isFalling)
        direction += sf::Vector2f(0, speed.y);

    if (direction.y != 0) {
        setPosition(sf::Vector2f(position.x, position.y + direction.y * seconds));

        Entity *b = world->getCollidingSolid(getBbox());
        while (b != NULL) {
            if (direction.y < 0)
                setPosition(sf::Vector2f(position.x, b->getBbox().top + b->getBbox().height));
            else {
                setPosition(sf::Vector2f(position.x, b->getBbox().top - getBbox().height));
                isFalling = false;
            }
            b = world->getCollidingSolid(getBbox());
        }

        //Walk on ladder
        b = world->getCollidingLadder(getBbox());
        if (b && b->getPosition().y > getBbox().top && isFalling && !input.Down) {
            setPosition(sf::Vector2f(position.x, b->getBbox().top - getBbox().height));
            isFalling = false;
        }
    }

    //Left Right - Up Down (ladder)
    if (!isFalling && !isCentring) {
        if (input.Left)
            direction -= sf::Vector2f(speed.x, 0);

        if (input.Right)
            direction += sf::Vector2f(speed.x, 0);
    }

    //Update X pos, and solve collisions
    if (direction.x != 0) {
        setPosition(sf::Vector2f(position.x + direction.x * seconds, position.y));


        Entity * b = world->getCollidingEnnemy(getBbox());
        if (b != NULL && b != this && b != world->getPlayer() && this != world->getPlayer()) {
            if (b->getPosition().x < getPosition().x)
                setPosition(getPosition() + sf::Vector2f(speed.x / 2 * seconds, 0));
            else
                setPosition(getPosition() - sf::Vector2f(speed.x / 2 * seconds, 0));
        }

        b = world->getCollidingSolid(getBbox());
        if (b != NULL) {
            if (direction.x < 0)
                setPosition(sf::Vector2f(b->getBbox().left + b->getBbox().width, position.y));
            else
                setPosition(sf::Vector2f(b->getBbox().left - getBbox().width, position.y));
        }


    }

    if (direction.x == 0)
        alignToGridX();

    if (direction.y == 0)
        alignToGridY();
}

void Character::setSpeed(sf::Vector2f speed) {
    this->speed = speed;
}

sf::Vector2f Character::getSpeed() {
    return speed;
}

void Character::align(sf::Vector2f pos) {
    if (!isFalling)
        setPosition(pos);
    else
        setPosition(sf::Vector2f(pos.x, getPosition().y));
}

void Character::alignToGridX() {
    setPosition(sf::Vector2f((int) (getCenter().x / Block::WIDTH) * Block::WIDTH + (Block::WIDTH - getBbox().width) / 2, getPosition().y));
}

void Character::alignToGridY() {
    setPosition(sf::Vector2f(getPosition().x, (int) (getCenter().y / Block::HEIGHT) * Block::HEIGHT));
}

void Character::setMoveable(bool canMove) {
    this->canMove = canMove;
}

void Character::setOrigin(sf::Vector2f origin) {
    this->origin = origin;
}

void Character::resetToOrigin() {
    setPosition(origin);
}