#include "gamemodel.h"

GameModel::GameModel()
{
    currentLevel = 0;
    Level* level = new Level();
    levels << level;
    gameMode = NORMAL;
}

void GameModel::update()
{
    levels[currentLevel]->update();
}

void GameModel::resetGame()
{

}
