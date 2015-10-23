#include "gamemodel.h"

GameModel::GameModel()
{
    currentLevel = 0;
    Level* level = new Level();
    levels << level;
}

void GameModel::update() {
    levels[currentLevel]->update();
}
