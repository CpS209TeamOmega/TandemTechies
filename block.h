#ifndef BLOCK_H
#define BLOCK_H

#include "entity.h"

class Block : public Entity
{
public:
    Block(Level* initLevel) : Entity(initLevel) { }
    Block(Level* initLevel, int initX, int initY) : Entity(initLevel, initX, initY) { }

    void update();

    void savePosition();
};

#endif // BLOCK_H
