#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "block.h"

class Level
{
    Player player;
    Block **blocks;

public:
    Level();
    ~Level();

    void update();

    void playerMvmnt();
};

#endif // LEVEL_H
