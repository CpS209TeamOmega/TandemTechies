#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player();

    //save the status of the player entity
    void keepMeHere();
};

#endif // PLAYER_H
