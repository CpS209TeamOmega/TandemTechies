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
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            if(blocks[y][x] != nullptr) {
                blocks[y][x]->update();
            }
        }
    }
    player->update();
    exit->update();

    xOffs = player->getX() - (GameWindow::WIDTH / 2);
    yOffs = player->getY() - (GameWindow::HEIGHT / 2);
}

void Level::load(QList<QString> data) {
    for(int y = 0; y < data.size(); y++) {
        QList<Block*> list;
        for(int x = 0; x < data[y].length(); x++) {
            QChar type = data[y].at(x);
            if(type == 'b') {
                list << new Block(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == 'p') {
                player = new Player(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == 'x') {
                exit = new Exit(this, x * Entity::SIZE, y * Entity::SIZE);
            } else if(type == ' ') {
                list << nullptr;
            }
        }
        blocks << list;
    }
}
