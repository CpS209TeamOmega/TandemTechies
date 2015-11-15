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
    bool removing; //Whether or not the player has picked it up
    int curSize;   //The size (for animation)
    int maxSize;   //The maximum animation size

public:
    //Creates the exit at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    Collectible(Level* initLevel, int initX, int initY);

    //Destructor for exit
    ~Collectible() { }

    //Checks to see if the player is touching the exit,
    //then sets the level to finished.
    void update();

    //Saves the exit's position to the save file.
    void savePosition(QTextStream &out);

    //Gets the score to add to the total score
    int getPoint() { return pointPlus; }

    //Deletes the collectible from the level and also from the GUI
    void deleteCollectible();

    //Sets the collectible to go away - similar to deleteLater();
    void setRemoving(bool isRemoving) { removing = isRemoving; }
};

#endif // COLLECTIBLE_H
