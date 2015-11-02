//**********************************************************
// File: level.cpp
// Desc: The implementation of the level class
//**********************************************************

#include "entity.h"
#include "collectible.h"
#include "level.h"
#include "gamewindow.h"
#include <QDebug>

Level::Level(QList<QString> data)
{
    load(data);
    finished = false;
    pointPlus = 1000;
}

Level::~Level() {
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            delete blocks[y][x];
        }
    }
    delete player;
    delete exit;
}

void Level::update() {
    //Update all objects in the game
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            if(blocks[y][x] != nullptr) {
                blocks[y][x]->update();
            }
        }
    }
    for(int i = 0; i < entities.size(); i++) {
        entities[i]->update();
    }
    player->update();
    exit->update();

    //Update the x and y offsets relative to the player
    xOffs = player->getX() + (player->getWidth() / 2) - (GameWindow::WIDTH / 2);
    yOffs = player->getY() + (player->getHeight() / 2) - (GameWindow::HEIGHT / 2);
}

bool Level::testCollision(int testX, int testY) {
    if(testX < 0 || testY < 0) return false; //Make sure the x and y are valid

    testX /= Entity::SIZE;					 //Make the x position the array x position
    testY /= Entity::SIZE;					 //Make the y position the array y position

    if(testX >= blocks[0].size()) return false; //Make sure the x is inside the level
    if(testY >= blocks.size()) return false;    //Make sure the y is inside the level

    return blocks[testY][testX] != nullptr;     //Return true if a block exists in that position
}

void Level::removeEntity(Entity *e) {
    entities.removeOne(e);
}

void Level::load(QList<QString> data) {
    for(int y = 0; y < data.size(); y++) {
        QList<Block*> list;							//The blocks in the current row
        for(int x = 0; x < data[y].length(); x++) {
            QChar type = data[y].at(x);
            if(type == 'b') {						//If the character represents a block
                list << new Block(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == 'p') {				//If the character represents the player
                list << nullptr;
                player = new Player(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == 'x') {
                list << nullptr;					//If the character is an exit
                exit = new Exit(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == 'c') {
                list << nullptr;
                entities << new Collectible(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == ' ') {				//If it is an empty space
                list << nullptr;
            }
        }
        blocks << list;								//Store the current row of blocks into the block list
    }
}

Block* Level::placeBlock(int x, int y){
    if(x < 0 || y < 0) return nullptr;

    x /= Entity::SIZE;					 //Make the x position the array x position
    y /= Entity::SIZE;					 //Make the y position the array y position

    if(x >= blocks[0].size()) return nullptr; //Make sure the x is inside the level
    if(y >= blocks.size()) return nullptr;    //Make sure the y is inside the level

    if(blocks[y][x] != nullptr) {
        blocks[y][x] = new Block(this, x * Entity::SIZE, y * Entity::SIZE);
        return blocks[y][x];
    }
    return nullptr;
}
