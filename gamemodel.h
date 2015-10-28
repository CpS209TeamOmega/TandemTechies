//**********************************************************
// File: gamemodel.h
// Desc: This is the model of the entire game. It includes
//          all of the game levels, the current level, and
//          methods to update and edit the game data.
//**********************************************************

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QList>

#include "level.h"
#include "scoremanager.h"

//The class containing all the data and methods
//for the entire game.
class GameModel
{
    QList<Level*> levels; //All of the current levels loaded into memory
    int currentLevel;     //The current level you are on in the levels QList
    QString levelDataFile;
    ScoreManager sm;      //The Score Manager

    //Game State  <---------Add more to here
    bool isFinished;
    bool isStarted;

public:
    GameModel();
    ~GameModel();

    //This method is called on every frame refresh.
    void update();

    //Resets the game, or basically creates a new game
    void resetGame();

    //Save game state
    void save();

    //Load game state
    void load();

    //Keyboard Press/Release Event
    void playerInputP(int p);
    void playerInputR(int r);

    //Loads the levels into the game so we can actually play
    bool loadLevels();

    //Returns the level the user is currently in.
    Level* getCurrentLevel() { return levels[currentLevel]; }


};

#endif // GAMEMODEL_H
