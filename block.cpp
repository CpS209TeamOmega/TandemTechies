//**********************************************************
// File: block.cpp
// Desc: The implementation of the block class
//**********************************************************

#include "level.h"
#include "block.h"

void Block::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
}

void Block::savePosition()
{

}
