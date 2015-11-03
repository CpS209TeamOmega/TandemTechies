//**********************************************************
// File: collectible.h
// Desc: A collectible in the game, which adds to the player's score
//**********************************************************

#ifndef COLLECTIBLE_H
#define COLLECTIBLE_H

#include "entity.h"
#include "scoremanager.h"

//The collectible entity, which finishes the game on player collision
class Collectible : public Entity {
    int pointPlus; //Score that this entity adds to the total score

public:
    //Creates the exit at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    Collectible(Level* initLevel, int initX, int initY) : Entity(initLevel, initX, initY), pointPlus(50) { }

    //Destructor for exit
    ~Collectible() { }

    //Checks to see if the player is touching the exit,
    //then sets the level to finished.
    void update();

    //Saves the exit's position to the save file.
    void savePosition();

    //Gets the score to add to the total score
    int getPoint() { return pointPlus; }

    //Deletes the collectible from the level and also from the GUI
    void deleteCollectible();
};

#endif // COLLECTIBLE_H
