#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QList>

#include "level.h"

class GameModel
{
    QList<Level*> levels; //All of the current levels loaded into memory
    int currentLevel;     //The current level you are on in the levels QList
    QString levelDataFile;

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


    void playerInput(int p);

    //Loads the levels into the game so we can actually play
    bool loadLevels();

    //Returns the level the user is currently in.
    Level* getCurrentLevel() { return levels[currentLevel]; }

};

#endif // GAMEMODEL_H
