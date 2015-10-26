#include "block.h"

Block::Block()
{
    placeable = false;
}

int Block::toBeAdded()
{
    if(placeable == true)
    {
        scorePlus = 100;
    }
}

void Block::update()
{

}

void Block::savePosition()
{

}
