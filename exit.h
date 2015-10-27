#ifndef EXIT_H
#define EXIT_H

#include "entity.h"

class Exit : public Entity {
public:
    Exit(Level* initLevel) : Entity(initLevel) { }
    Exit(Level* initLevel, int initX, int initY) : Entity(initLevel, initX, initY) { }

    void update();

    void savePosition();
};

#endif // EXIT_H
