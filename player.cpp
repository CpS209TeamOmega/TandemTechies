//**********************************************************
// File: player.cpp
// Desc: The player's implementation, which updates the
//          player and moves him according to keys pressed
//**********************************************************

#include "level.h"
#include <QTcpSocket>
#include "sound.h"


Player::Player(Level *initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    hSpeed = 8;
    vSpeed = 0;
    right = left = jumping = jumpKeyPressed = dead = cheat = false;
    jumpDistance = 0;
    jumpHeight = 192;
    maxVSpeed = 32;
    dir = 1;
    jumpSpeed = -12;
	pLeft.load(":/images/p_left.png");
	pRight.load(":/images/p_right.png");
    touched = true;
    vibrate = false;
    times = 0;
}

void Player::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(!jumping) {		//If the player is not currently jumping
        if(level->testCollision(getX(), getY() + getHeight() + vSpeed)    //Test to see if there is a block underneath
                || level->testCollision(getX() + getWidth() - hSpeed, getY() + getHeight() + vSpeed)) {
            while(getY() % Entity::SIZE != 0) addY(1);
            vSpeed = 0;
            if (!touched){vibrate = true; touched = true; Sound::instance().hitGround();}
            times++;
            if(times > 50){vibrate = false; times = 0;}

            if(jumpKeyPressed) jumping = true;		//If player is on a block and trying to jump, jump
        } else {
            touched = false;
            vibrate = false;
            times = 0;
            vSpeed += 1;							//Make the player fall with the illusion of gravity
            if(vSpeed > maxVSpeed) vSpeed = maxVSpeed;
        }
    } else if(jumpKeyPressed) {
        if(level->testCollision(getX(), getY() + jumpSpeed)		//If the player hits his head
                || level->testCollision(getX() + getWidth() - hSpeed, getY() + jumpSpeed)) {
            while(getY() % Entity::SIZE != 0) addY(-1);
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
        if(right && !level->testCollision(getX() + getWidth(), getY()) && !level->testCollision(getX() + getWidth(), getY() + getHeight() - 1)) {
            addX(hSpeed);	//Move right
			dir = 1;
        } else if(left && !level->testCollision(getX() - hSpeed, getY()) && !level->testCollision(getX() - hSpeed, getY() + getHeight() - 1)) {
            addX(-hSpeed);  //Move left
			dir = -1;
        }
    }

	if (dir == -1) {
        buddy->setPixmap(pLeft);
	} else {
        buddy->setPixmap(pRight);
	}
}

void Player::clearFlags() {
    jumpKeyPressed = false;
    right = false;
    left = false;
}

void Player::savePosition(QTextStream &out) {
    out << "Player " << getX() << " " << getY() << " " << dir << "\n";
}

void Player::setCheatJumpHeight(){
    if (!cheat)
        {jumpHeight = 1920; hSpeed = 20; jumpSpeed = -30; cheat = true; Sound::instance().cheatOn();}
   else
        {jumpHeight = 192; hSpeed = 8; jumpSpeed = -12; cheat = false; Sound::instance().cheatOff();}
}
