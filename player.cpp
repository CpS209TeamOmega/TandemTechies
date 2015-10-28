//**********************************************************
// File: player.cpp
// Desc: The player's implementation, which updates the
//          player and moves him according to keys pressed
//**********************************************************

#include "level.h"
#include "player.h"

Player::Player(Level *initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    velocity = 10;
    right = false;
    left = false;
}

void Player::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(!(right && left)) {
        if(right && !level->testCollision(getX() + getWidth(), getY())) {
            addX(velocity);
        } else if(left && !level->testCollision(getX(), getY())) {
            addX(-velocity);
        }
    }
}

void Player::savePosition() {

}
