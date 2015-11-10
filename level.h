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
#include "gamemodel.h"
#include "block.h"
#include "player.h"
#include "remoteplayer.h"
#include "exit.h"

//Forward declaration of the entity class, since level
//refers to entity and entity refers to level.
class Entity;

//Forward declaration of the gamemodel class, since
//level refers to gamemodel and vice versa
class GameModel;

//The main class for level manipulation
class Level
{
private:
    QList<QString> data;         //The level's data (for resetting and loading)
    Player* player;             //The player
    RemotePlayer* remotePlayer; //The other player
    Exit* exit;                 //The level's exit
    QList<QList<Block*>> blocks;//All of the blocks inside the level
    QList<Entity*> entities;    //All of the entities in the game
    int numBlocks;              //The number of placeable blocks
    QString name;               //The level's name
    int pointPlus;              //points added at level completion
    int xOffs;                  //The x offset of the player (side-scrolling)
    int yOffs;                  //The y offset of the player (side-scrolling)
    GameModel* model;
    int scoreBeforeLevel;

    bool finished;              //If the level is finished

public:
    //Creates a level with the map data, parsing
    //in the data and making objects
    //<data> The map data, stored in levels.dat
    Level(QList<QString> &initData, GameModel* model);

    //Deletes the level and pointers inside of it
    ~Level();

    //Updates all of the entities inside the level
    void update();

    //Loads the level with the data
    void load();

    //Tests if there is a block at a certain point
    bool testCollision(int testX, int testY);

    //Removes an entity from the QList of entities
    void removeEntity(Entity* e);

    //Remotes all entities
    void removeAllEntities();

    //Removes the block at the position given
    void removeBlock(int x, int y);
    PlaceableBlock* removeBlockX();

    //Place block in certain position
    PlaceableBlock* placeBlock(int x, int y);
    PlaceableBlock* placeBlock ();


    //Setters
    void setName(QString newName) { name = newName; }
    void setNumBlocks(int newNum) { numBlocks = newNum; }
    void setFinished(bool newFinished) { finished = newFinished; }
    void setRemotePlayer(RemotePlayer* rm) { remotePlayer = rm; }

    //Getters
    Player* getPlayer() { return player; }
    RemotePlayer* getRemotePlayer() { return remotePlayer; }
    Exit* getExit() { return exit; }
    QList<QList<Block*>>& getBlocks() { return blocks; }
    QList<Entity*>& getEntities() { return entities; }
    int getPoints() { return pointPlus; }
    int getXOffs() { return xOffs; }
    int getYOffs() { return yOffs; }
    bool isFinished() { return finished; }
	QString getName() { return name; }
    int getNumBlocks() { return numBlocks; }
    QList<QString>& getData() { return data; }
    int getScoreBeforeLevel() { return scoreBeforeLevel; }

};

#endif // LEVEL_H
