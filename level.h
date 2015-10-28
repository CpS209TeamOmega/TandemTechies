//**********************************************************
// File: level.h
// Desc: This is the class for each level in the game. It
//          includes the player, exit, enemies, blocks, and
//          methods to update all of these.
//**********************************************************

#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "block.h"
#include "exit.h"
#include <QString>
#include <QList>

//Forward declaration of the entity class, since level
//refers to entity and entity refers to level.
class Entity;

//The main class for level manipulation
class Level
{
    Player* player;             //The player
    Exit* exit;                 //The level's exit
    QList<QList<Block*>> blocks;//All of the blocks inside the level
    int numBlocks;              //The number of placeable blocks
    QString name;               //The level's name
    int xOffs;                  //The x offset of the player (side-scrolling)
    int yOffs;                  //The y offset of the player (side-scrolling)

    //Level State
    bool finished;


public:
    //Creates a level with the map data, parsing
    //in the data and making objects
    //<data> The map data, stored in levels.dat
    Level(QList<QString> data);

    //Deletes the level and pointers inside of it
    ~Level();

    //Updates all of the entities inside the level
    void update();

    //Loads the level with the data
    void load(QList<QString> data);

    //Setters
    void setName(QString newName) { name = newName; }
    void setNumBlocks(int newNum) { numBlocks = newNum; }

    //Getters
    Player* getPlayer() { return player; }
    Exit* getExit() { return exit; }
    QList<QList<Block*>>& getBlocks() { return blocks; }
    int getXOffs() { return xOffs; }
    int getYOffs() { return yOffs; }

};

#endif // LEVEL_H
