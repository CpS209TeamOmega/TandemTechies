#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
    bool jumping, falling;
    int velocity;

public:
    Player() : Entity() { }
    Player(int initX, int initY) : Entity(initX, initY) { }

    void update();

    //save the status of the player entity
    void savePosition();
};

#endif // PLAYER_H
