//**********************************************************
// File: entity.cpp
// Desc: The implementation of the entity class
//**********************************************************

#include "level.h"
#include "entity.h"

//The default entity size
int Entity::SIZE = 64;

bool Entity::isCollidingWith(Entity *otherEntity)
{
    return rect.intersects(otherEntity->getRect());
}
