#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
public:
    Player();

    //saves position and such of player entity
    void keepMeHere();
};

#endif // PLAYER_H
