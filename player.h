//**********************************************************
// File: player.h
// Desc: The class for the player and all of the operations
//          on the player. This is the class that is used
//          for actually playing the game
//**********************************************************

#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class Player : public Entity {
    bool jumping, falling; //Whether or not the player is jumping or falling
    bool left, right;      //Whether or not the left or right key is pressed
    int velocity;          //The player's velocity
    int fallingVelocity;

public:
    //Creates the player using the default entity constructor
    //<initLevel> The level that the entity is inside
    Player(Level* initLevel) : Entity(initLevel) { }

    //Creates the player at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    Player(Level* initLevel, int initX, int initY);

    //Destructor for player
    ~Player() { }

    //Updates the player - all of the code for movement and such
    void update();

    //save the status of the player entity
    void savePosition();

    //Setters
    void setRight(bool newRight) { right = newRight; }
    void setLeft(bool newLeft) { left = newLeft; }
    void setJumping(bool newJumpig) { if(newJumpig){ jumping = true; } else { jumping = false; } }
};

#endif // PLAYER_H
