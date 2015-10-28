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
    fallingVelocity = 0;
}

void Player::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
    fallingVelocity += 1;
    addY(fallingVelocity);
    if(!(right && left)) {
        if(right) {
            addX(velocity);
        } else if(left) {
            addX(-velocity);
        }
    }
}

void Player::savePosition() {

}
