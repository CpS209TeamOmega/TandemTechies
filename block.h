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

public:
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

    //getters
    int getScorePlus() { return scorePlus; }
};

class PlaceableBlock : public Block
{
private:
    int curSize;
    bool deleting;
    bool creating;

public:
    //Creates the placeable block at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    PlaceableBlock(Level* initLevel, int initX, int initY) : Block(initLevel, initX, initY), curSize(0), deleting(false), creating(true) { }

    //Updates the block. The animation is updated also
    void update();

    //Saves the block's position to the save file
    void savePosition();

    //When the user presses space to pick up a block, this method is called, which
    //makes the block shrink and delete
    void setCreating(bool isCreating) { creating = isCreating; }
    void setDeleting(bool isDeleting) { deleting = isDeleting; }

    //Test if the block is deleting or not
    bool isDeleting() { return deleting; }

    bool isCreating() { return creating; }
};

#endif // BLOCK_H
