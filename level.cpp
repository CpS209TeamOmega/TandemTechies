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
    name = "";
    load(data);
    finished = false;
    xOffs = 0;
    yOffs = 0;
}

Level::~Level() {
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            delete blocks[y][x];
        }
    }
    for(int i = 0; i < entities.size(); i++) {
        delete entities[i];
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
    delete e;
}

void Level::load(QList<QString> initData) {
    data = QList<QString>(initData);

    for(int y = 0; y < initData.size(); y++) {
        QList<Block*> list;							//The blocks in the current row
        for(int x = 0; x < initData[y].length(); x++) {
            QChar type = initData[y].at(x);
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
                Collectible* c = new Collectible(this, x * Entity::SIZE, y * Entity::SIZE);
                entities << c;
            } else if(type == 'm') {
                Block* b = new Block(this, x * Entity::SIZE, y * Entity::SIZE);
                b->setPlaceable(true);
                list << b;
            } else if(type == ' ') {				//If it is an empty space
                list << nullptr;
            }
        }
        blocks << list;								//Store the current row of blocks into the block list
    }
}

Block* Level::placeBlock(){
    int x = 0, y = 0;
    if(player->getDir() == -1){
        x = player->getX() - Entity::SIZE + 2;
        y = player->getY();
    } else if(player->getDir() == 1){
        x = player->getX() + Entity::SIZE * 2 - 2;
        y = player->getY();
    }

    if(x < 0 || y < 0) return nullptr;

    x /= Entity::SIZE;					 //Make the x position the array x position
    y /= Entity::SIZE;					 //Make the y position the array y position

    if(x >= blocks[0].size()) return nullptr; //Make sure the x is inside the level
    if(y >= blocks.size()) return nullptr;    //Make sure the y is inside the level

    if(blocks[y][x] == nullptr) {
        if(numBlocks) {
            Block* b = new Block(this, x * Entity::SIZE, y * Entity::SIZE);
            for(int i = 0; i < entities.size(); i++) {
                if(entities[i]->isCollidingWith(b)) {
                    delete b;
                    return nullptr;
                }
            }
            if(exit->isCollidingWith(b)) {
                delete b;
                return nullptr;
            }
            if(testCollision(b->getX(), b->getY() + Entity::SIZE)) {
                b->setPlaceable(true);
                blocks[y][x] = b;
                numBlocks--;
                return blocks[y][x];
            } else {
                delete b;
                return nullptr;
            }
        }
    } else {
        Block* testBlock = blocks[y][x];
        if(testBlock->isPlaceable()) {
            testBlock->getBuddy()->deleteLater();
            delete testBlock;
            blocks[y][x] = nullptr;
            numBlocks++;
        }
    }

    return nullptr;
}
