//**********************************************************
// File: player.cpp
// Desc: The player's implementation, which updates the
//          player and moves him according to keys pressed
//**********************************************************

#include "level.h"
#include "player.h"

void Player::update() {
    addX(5);
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
>>>>>>> upstream/master
}

void Player::savePosition()
{


}
