#ifndef LEVEL_H
#define LEVEL_H

#include <QList>

#include "entity.h"
#include "block.h"
#include "collectibles.h"
#include "player.h"

class Level
{
    Player player;

    //list of the blocks within a level
    //these do not have the possibility of adding points
    QList<Block *> blocks;
    //list of the collectibles within a level
    QList<Collectibles *> collectibles;

public:
    Level();
    ~Level();

    void update();
};

#endif // LEVEL_H
