//**********************************************************
// File: exit.cpp
// Desc: The implementation of the exit class
//**********************************************************

#include "level.h"
#include "exit.h"

void Exit::update() {
    //See if the player has finished the level
    if(isCollidingWith(level->getPlayer())) {
        level->setFinished(true);
    }

    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
}

void Exit::savePosition() {

}
