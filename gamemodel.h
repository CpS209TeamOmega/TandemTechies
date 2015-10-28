#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QList>

#include "level.h"
#include "scoremanager.h"

class GameModel
{
    //All of the current levels loaded into memory
    QList<Level*> levels;

    //The current level you are on in the levels QList
    int currentLevel;

    enum Mode {CHEAT, NORMAL, HARD};
    Mode gameMode;

    //current mode
    bool curMode;

    //difficulty levels
    //if xMode == true.... apply things....
    bool cheatMode;
    bool normalMode;
    bool hardMode;

public:
    GameModel();

    //This method is called on every frame refresh.
    void update();

    //Resets the game, or basically creates a new game
    void resetGame();

    //Save game state
    void save();

    //Load game state
    void load();

    //getters
    int getLevel() { return currentLevel; }
    bool getCheatMode() { return cheatMode; }
    bool getNormMode() { return normalMode; }
    bool getHardMode() { return hardMode; }

    //setters
    void setMode(bool newCurMode) { curMode = newCurMode; }

};

#endif // GAMEMODEL_H
