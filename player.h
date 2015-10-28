#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "block.h"

class Player : public Entity
{
    bool jumping, falling;
    int velocity;

    //these have the possiblity of adding points
//    QList<Block *> blockInventory;

public:
    Player();

    void update();

    //save the status of the player entity
    void savePosition();
};

#endif // PLAYER_H
