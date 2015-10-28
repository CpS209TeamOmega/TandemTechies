//**********************************************************
// File: player.cpp
// Desc: The player's implementation, which updates the
//          player and moves him according to keys pressed
//**********************************************************

#include "level.h"
#include "player.h"

Player::Player(Level *initLevel) : Entity(initLevel) {
    hSpeed = 12;
    vSpeed = 0;
    right = left = jumping = falling = jumpKeyPressed = false;
    jumpDistance = 0;
    jumpHeight = 64;
    maxVSpeed = 32;
	jumpSpeed = -16;
}

Player::Player(Level *initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    hSpeed = 12;
    vSpeed = 0;
    right = left = jumping = falling = jumpKeyPressed = false;
    jumpDistance = 0;
    jumpHeight = 96;
    maxVSpeed = 32;
	jumpSpeed = -16;
}

void Player::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(!jumping) {
        if(level->testCollision(getX() + 20, getY() + getHeight())
                || level->testCollision(getX() + getWidth() - 20, getY() + getHeight())) {
            vSpeed = 0;
            while(getY() % Entity::SIZE != 0) addY(-2);
            if(jumpKeyPressed) jumping = true;
        } else {
            vSpeed += 2;
            if(vSpeed > maxVSpeed) vSpeed = maxVSpeed;
        }
    } else {
        if(level->testCollision(getX() + 20, getY() + jumpSpeed)
                || level->testCollision(getX() + getWidth() - 20, getY() + jumpSpeed)) {
            while(getY() % Entity::SIZE != 0) addY(2);
            vSpeed = 0;
            jumping = false;
            jumpDistance = 0;
        } else {
            vSpeed = jumpSpeed;
            jumpDistance -= vSpeed;
            if(jumpDistance >= jumpHeight) {
                jumpDistance = 0;
                jumping = false;
            }
        }
    }

    addY(vSpeed);

    if(!(right && left)) {
        if(right && !level->testCollision(getX() + getWidth(), getY()) && !level->testCollision(getX() + getWidth(), getY() + getHeight() - 2)) {
            addX(hSpeed);
        } else if(left && !level->testCollision(getX(), getY()) && !level->testCollision(getX(), getY() + getHeight() - 2)) {
            addX(-hSpeed);
        }
    }
}

void Player::savePosition()
{

}
