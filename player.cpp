#include "level.h"
#include "player.h"



void Player::update() {
    addX(5);
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
}

void Player::savePosition() {


}
