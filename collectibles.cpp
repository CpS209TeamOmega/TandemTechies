#include "collectibles.h"

Collectibles::Collectibles()
{
    collected = false;
}

void Collectibles::deleteCollectible()
{
    if(isCollidingWith() == true)
    {
        collected = true;
        //delete that Collectible instance
    }
}


