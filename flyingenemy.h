//**********************************************************
// File: flyingenemy.h
// Desc: The class for the flying enemy and all of the operations
//          on the FlyingEnemy.
//**********************************************************
#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H
#include "entity.h"
#include "sound.h"
#include <QPixmap>

class FlyingEnemy : public Entity {
    int hSpeed;					  //The FlyingEnemy's velocity
    int dir;					  //The direction the FlyingEnemy is currently facing
    bool dead;                    //If the FlyingEnemy is dead
    int curHeight;                //For the dead animation

    QPixmap flyingEnemy, flyingEnemy2;

public:
    //Creates the FlyingEnemy at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    FlyingEnemy(Level* initLevel, int initX, int initY);

    //Destructor for FlyingEnemy
    ~FlyingEnemy() { }

    //Updates the FlyingEnemy - all of the code for movement and such
    void update();

    //Save the status of the FlyingEnemy entity
    void savePosition(QTextStream &out);

    //Getters
    int getDir() { return dir; }

    //Setters
    void setDir(int newDir) { dir = newDir; }
    void setDead(bool d){ dead = d; Sound::instance().killedEnemy(); }
};


#endif // FLYINGENEMY_H
