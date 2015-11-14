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

	//Update the exit's label according to the player's position (side-scrolling)
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
}
