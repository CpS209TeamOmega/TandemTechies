#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity
{
    bool jumping, falling;

public:
    Player();

    void update();
};

#endif // PLAYER_H
