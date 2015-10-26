#ifndef BLOCK_H
#define BLOCK_H

#include "entity.h"

class Block : public Entity
{
public:
    Block() : Entity() { }
    Block(int initX, int initY) : Entity(initX, initY) { }
    ~Block() { }

    void update();

    void savePosition();
};

#endif // BLOCK_H
