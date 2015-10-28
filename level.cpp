//**********************************************************
// File: level.cpp
// Desc: The implementation of the level class
//**********************************************************

#include "entity.h"
#include "level.h"
#include "gamewindow.h"
#include <QDebug>

Level::Level(QList<QString> data)
{
    load(data);
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
    player->update();
    exit->update();

    //Update the x and y offsets relative to the player
    xOffs = player->getX() - (GameWindow::WIDTH / 2);
    yOffs = player->getY() - (GameWindow::HEIGHT / 2);
}

bool Level::testCollision(int testX, int testY) {
    testX /= Entity::SIZE;
    testY /= Entity::SIZE;

    if(testX < 0 || testX > blocks[0].size()) return false;
    if(testY < 0 || testY > blocks.size()) return false;

    qDebug() << testX << "   " << testY;
    return blocks[testY][testX] != nullptr;
}

void Level::load(QList<QString> data) {
    for(int y = 0; y < data.size(); y++) {
        QList<Block*> list;
        for(int x = 0; x < data[y].length(); x++) {
            QChar type = data[y].at(x);
            if(type == 'b') {
                list << new Block(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == 'p') {
                list << nullptr;
                player = new Player(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == 'x') {
                list << nullptr;
                exit = new Exit(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == ' ') {
                list << nullptr;
            }
        }
        blocks << list;
    }
}
