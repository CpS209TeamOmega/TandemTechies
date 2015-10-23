#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
    bool jumping, falling;
    int velocity;

public:
    Player();

    void update();

    //save the status of the player entity
    void savePosition();
};

#endif // PLAYER_H
