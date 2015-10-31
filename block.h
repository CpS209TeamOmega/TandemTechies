//**********************************************************
// File: block.h
// Desc: The solid block inside the game - it is basically
//          what makes every level, or the platform of the game
//**********************************************************

#ifndef BLOCK_H
#define BLOCK_H

#include "entity.h"

//The block or default entity in the game
class Block : public Entity
{
private:
    //score that a block adds to total score (if it is placeable)
    int scorePlus;

    //whether or not an inventory block has been placed
    bool placeable;

public:
    //Creates the block using the default entity constructor
    //<initLevel> The level that the entity is inside
    Block(Level* initLevel) : Entity(initLevel) { }

    //Creates the block at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    Block(Level* initLevel, int initX, int initY) : Entity(initLevel, initX, initY) { }

    //Destructor for block
    ~Block() { }

    //Updates the block. All that is done here is setting
    //the position of the block to reflect the player's position
    void update();

    //Saves the block's position to the save file
    void savePosition();

    //returns an amount to be added
    int toBeAdded();

    //getters
    int getScorePlus() { return scorePlus; }
    bool isPlaceable() { return placeable; }

    //setters
    void setPlaceable(bool isPlaceable) { placeable = isPlaceable; }
};

#endif // BLOCK_H
