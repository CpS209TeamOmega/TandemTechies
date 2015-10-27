#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QList>

#include "level.h"

class GameModel
{
    QList<Level*> levels;
    int currentLevel;

public:
    GameModel();

    void update();

    //save and load functions
    void save();
    void load();

    void playerInput(int p);
};

#endif // GAMEMODEL_H
