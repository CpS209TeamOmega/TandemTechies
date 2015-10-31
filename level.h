//**********************************************************
// File: level.h
// Desc: This is the class for each level in the game. It
//          includes the player, exit, enemies, blocks, and
//          methods to update all of these.
//**********************************************************

#ifndef LEVEL_H
#define LEVEL_H

#include <QList>

#include "entity.h"
#include "block.h"
#include "player.h"
#include "exit.h"

//Forward declaration of the entity class, since level
//refers to entity and entity refers to level.
class Entity;

//The main class for level manipulation
class Level
{
private:
    Player* player;             //The player
    Exit* exit;                 //The level's exit
    QList<QList<Block*>> blocks;//All of the blocks inside the level
    QList<Entity*> entities;    //All of the entities in the game
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

    //Tests if there is a block at a certain point
    bool testCollision(int testX, int testY);

    //Removes an entity from the QList of entities
    void removeEntity(Entity* e);

    //Place block in certain position
    Block* placeBlock ();


    //Setters
    void setName(QString newName) { name = newName; }
    void setNumBlocks(int newNum) { numBlocks = newNum; }
    void setFinished(bool newFinished) { finished = newFinished; }

    //Getters
    Player* getPlayer() { return player; }
    Exit* getExit() { return exit; }
    QList<QList<Block*>>& getBlocks() { return blocks; }
    QList<Entity*>& getEntities() { return entities; }
    int getXOffs() { return xOffs; }
    int getYOffs() { return yOffs; }
    bool isFinished() { return finished; }
	QString getName() { return name; }
	int getNumBlocks() { return numBlocks; }

};

#endif // LEVEL_H
