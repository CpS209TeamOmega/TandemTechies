//**********************************************************
// File: block.cpp
// Desc: The implementation of the block class
//**********************************************************

#include "level.h"
#include "block.h"

void Block::update() {
	//Update the label's position according to the player (side-scrolling)
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
}

void Block::savePosition()
{

}

void PlaceableBlock::update() {
    if(!deleting) {
        if(curSize < Entity::SIZE) {
            curSize += 8;
            buddy->setGeometry(getX() + (Entity::SIZE / 2 - curSize / 2) - level->getXOffs(), getY() + (Entity::SIZE / 2 - curSize / 2) - level->getYOffs(), curSize, curSize);
        } else {
            creating = false;

            //Updates the label's position according to the player (side-scrolling)
            buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
        }
    } else {
        if(curSize > 0) {
            curSize -= 8;
            buddy->setGeometry(getX() + (Entity::SIZE / 2 - curSize / 2) - level->getXOffs(), getY() + (Entity::SIZE / 2 - curSize / 2) - level->getYOffs(), curSize, curSize);
        } else {
            buddy->deleteLater();
            level->removeBlock(getX() / Entity::SIZE, getY() / Entity::SIZE);
        }
    }
}

void PlaceableBlock::savePosition() {

}
