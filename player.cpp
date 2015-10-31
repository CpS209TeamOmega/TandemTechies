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
    jumpHeight = 192;
    maxVSpeed = 32;
	jumpSpeed = -16;
}

Player::Player(Level *initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    hSpeed = 8;
    vSpeed = 0;
    right = left = jumping = falling = jumpKeyPressed = false;
    jumpDistance = 0;
    jumpHeight = 192;
    maxVSpeed = 32;
	jumpSpeed = -16;
}

void Player::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(!jumping) {		//If the player is not currently jumping
        if(level->testCollision(getX() + hSpeed + 1, getY() + getHeight())    //Test to see if there is a block underneath
                || level->testCollision(getX() + getWidth() - hSpeed - 1, getY() + getHeight())) {
            vSpeed = 0;
            while(getY() % Entity::SIZE != 0) addY(-2);
            if(jumpKeyPressed) jumping = true;		//If player is on a block and trying to jump, jump
        } else {
            vSpeed += 2;							//Make the player fall with the illusion of gravity
            if(vSpeed > maxVSpeed) vSpeed = maxVSpeed;
        }
    } else if(jumpKeyPressed) {
        if(level->testCollision(getX() + hSpeed + 1, getY() + jumpSpeed)		//If the player hits his head
                || level->testCollision(getX() + getWidth() - hSpeed - 1, getY() + jumpSpeed)) {
            while(getY() % Entity::SIZE != 0) addY(2);
            vSpeed = 0;
            jumping = false;
            jumpDistance = 0;
        } else { //Keep moving upward!
            vSpeed = jumpSpeed;
            jumpDistance -= vSpeed;
            if(jumpDistance >= jumpHeight) {
                jumpDistance = 0;
                vSpeed = 0;
                jumping = false;
            }
        }
    } else {
        jumping = false;
        jumpDistance = 0;
        vSpeed = 0;
    }

    addY(vSpeed);		//Actually perform the vertical movement

    if(!(right && left)) {	//Make sure the user isn't pressing right and left (why?....)
        if(right && !level->testCollision(getX() + getWidth(), getY()) && !level->testCollision(getX() + getWidth(), getY() + getHeight() - 2)) {
            addX(hSpeed);	//Move right
        } else if(left && !level->testCollision(getX(), getY()) && !level->testCollision(getX(), getY() + getHeight() - 2)) {
            addX(-hSpeed);  //Move left
        }
    }
}

void Player::savePosition()
{

}
