#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
    bool jumping, falling;

public:
    Player();

    void update();

    //save the status of the player entity
    void keepMeHere();
};

#endif // PLAYER_H
