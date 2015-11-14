//**********************************************************
// File: enemy.h
// Desc: The class for the enemy and all of the operations
//          on the enemy.
//**********************************************************

#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include "sound.h"
#include <QPixmap>

class Enemy : public Entity {
    int hSpeed;					  //The enemy's velocity
    int dir;					  //The direction the enemy is currently facing
    bool dead;                    //If the enemy is dead
    int curHeight;                //For the dead animation

    QPixmap eLeft, eRight;

public:
    //Creates the enemy at a certain position
    //<initLevel> The level that the entity is inside
    //<initX> The starting x position of the exit
    //<initY> The starting y position of the exit
    Enemy(Level* initLevel, int initX, int initY);

    //Destructor for enemy
    ~Enemy() { }

    //Updates the enemy - all of the code for movement and such
    void update();

    //Save the status of the enemy entity
    void savePosition(QTextStream &out);

    //Getters
    int getDir() { return dir; }

    //Setters
    void setDir(int newDir) { dir = newDir; }
    void setDead(bool die) {dead = die;Sound::instance().killedEnemy();}
};

#endif // ENEMY_H
