#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
    bool jumping, falling;
    int velocity;


public:
    Player(Level* initLevel) : Entity(initLevel) { }
    Player(Level* initLevel, int initX, int initY) : Entity(initLevel, initX, initY) { }

    void update();

    //save the status of the player entity
    void savePosition();
};

#endif // PLAYER_H
