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
#include "remoteplayer.h"
#include "player.h"

//The class containing all the data and methods
//for the entire game.
class GameModel : public QObject
{
    Q_OBJECT

    QLabel* back;
    QList<Level*> levels; //All of the current levels loaded into memory
    int currentLevel;     //The current level you are on in the levels QList
    QString levelDataFile;//The level's data file name
    bool updateGUI;       //When the GUI must be updated to reflect model state
    int lives;

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
    bool load();

    //Called when the level is finished
    void levelFinished();

    //Places a block in the level
    PlaceableBlock* placeBlock();
    PlaceableBlock* removeBlock();
    PlaceableBlock* placeBlock(int x, int y);

    //Keyboard Press/Release Event
    void playerInputP(int p);
    void playerInputR(int r);

    //Loads the levels into the game so we can actually play
    bool loadLevels();

    //Restarts the current level
    void resetCurrentLevel();

    //Getters
    int getLives() { return lives; }
    bool mustUpdateGUI() { return updateGUI; }
    int getLevelNumber() { return currentLevel + 1; }
    Level* getCurrentLevel() { return levels[currentLevel]; }

    //Setters
    void setCurrentLevel(int newLevel);
    void setBackground(QLabel* newBack) { back = newBack; }
    void setUpdateGUI(bool newValue) { updateGUI = newValue; }
    void setLives(int newLives) { lives = newLives; }

signals:
    void gameFinished(bool done);
};

#endif // GAMEMODEL_H
