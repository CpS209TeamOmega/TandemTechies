#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "block.h"
#include "collectibles.h"

class Level
{
    Player player;
    Block **blocks;
    QList<Collectibles *> collectibleList;//All of the collectibles within a level

public:
    Level();
    ~Level();

    void update();
};

#endif // LEVEL_H
