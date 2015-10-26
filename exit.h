#ifndef EXIT_H
#define EXIT_H

#include "entity.h"

class Exit : public Entity
{
public:
    Exit() : Entity() { }
    Exit(int initX, int initY) : Entity(initX, initY) { }

    void update();

    void savePosition();
};

#endif // EXIT_H
