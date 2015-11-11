//**********************************************************
// File: exit.h
// Desc: The declaration of the exit entity. This entity
//          finishes the level when the player touches it.
//**********************************************************

#ifndef EXIT_H
#define EXIT_H

#include "entity.h"

//The exit entity, which finishes the game on player collision
class Exit : public Entity {
public:
    //Creates the exit at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    Exit(Level* initLevel, int initX, int initY) : Entity(initLevel, initX, initY) { }

    //Destructor for exit
    ~Exit() { }

    //Checks to see if the player is touching the exit,
    //then sets the level to finished.
    void update();

    //Saves the exit's position to the save file.
    void savePosition(QTextStream&) { }
};

#endif // EXIT_H
