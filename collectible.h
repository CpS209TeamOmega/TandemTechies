//**********************************************************
// File: collectible.h
// Desc: A collectible in the game, which adds to the player's score
//**********************************************************

#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "entity.h"

//The collectible entity, which finishes the game on player collision
class Collectible : public Entity {
    int scorePlus; //Score that this entity adds to the total score

public:
    //Creates the collectible using the default entity constructor
    //<initLevel> The level that the entity is inside
    Collectible(Level* initLevel) : Entity(initLevel) { }

    //Creates the exit at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    Collectible(Level* initLevel, int initX, int initY) : Entity(initLevel, initX, initY) { }

    //Destructor for exit
    ~Collectible() { }

    //Checks to see if the player is touching the exit,
    //then sets the level to finished.
    void update();

    //Saves the exit's position to the save file.
    void savePosition();

    //Gets the score to add to the total score
    int getScorePlus() { return scorePlus; }

    //Deletes the collectible from the level and also from the GUI
    void deleteCollectible();
};

#endif // COLLECTIBLE_H
