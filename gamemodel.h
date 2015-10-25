#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QList>
#include "level.h"

class GameModel
{
    QList<Level*> levels; //All of the current levels loaded into memory
    int currentLevel;     //The current level you are on in the levels QList

    //current mode
    bool curMode;

    //difficulty levels
    bool easyMode;
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
    bool getEasyMode() { return easyMode; }
    bool getNormMode() { return normalMode; }
    bool getHardMode() { return hardMode; }

    //setters
    void setMode(bool newCurMode) { curMode = newCurMode; }

};

#endif // GAMEMODEL_H
