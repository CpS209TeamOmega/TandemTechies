//**********************************************************
// File: level.cpp
// Desc: The implementation of the level class
//**********************************************************

#include "entity.h"
#include "collectible.h"
#include "level.h"
#include "gamewindow.h"
#include "network.h"
#include "scoremanager.h"
#include "enemy.h"
#include "sound.h"
#include <QDebug>

Level::Level(QList<QString> &initData, GameModel *initModel)
    : data(initData), model(initModel) {
    data = initData;
    finished = false;
    xOffs = 0;
    yOffs = 0;
    player = nullptr;
    remotePlayer = nullptr;
    exit = nullptr;
    scoreBeforeLevel = 0;
    amplitudeH = amplitudeW = 0;
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
    delete exit;
    delete player;
}

void Level::update() {
    //Update all objects in the game
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            if(blocks[y][x]) {
                blocks[y][x]->update();
            }
        }
    }
    for(int i = 0; i < entities.size(); i++) {
        entities[i]->update();
    }
    player->update();
    exit->update();

    //check vibrate
    if(getPlayer()->getVib()){
        amplitudeH = rand() % 10 - 5;
        amplitudeW = rand() % 10 - 5;
    }else{
        amplitudeH = amplitudeW = 0;
    }

    //Update the x and y offsets relative to the player
    xOffs = player->getX() + (player->getWidth() / 2) - (GameWindow::WIDTH / 2) + amplitudeW;
    yOffs = player->getY() + (player->getHeight() / 2) - (GameWindow::HEIGHT / 2) + amplitudeH;
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

void Level::removeAllEntities() {
    for(int i = 0; i < entities.size(); i++) {
        delete entities[i];
    }
    entities.clear();
}

void Level::removePlaceableBlocks() {
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            PlaceableBlock* b = dynamic_cast<PlaceableBlock*>(blocks[y][x]);
            if(b) {
                delete b;
                blocks[y][x] = nullptr;
            }
        }
    }
}

void Level::removeBlock(int x, int y) {
    delete blocks[y][x];
    blocks[y][x] = nullptr;
}

void Level::load() {
    scoreBeforeLevel = ScoreManager::instance().getCurScore();
    name = data[0].mid(6);
    numBlocks = data[1].mid(7).toInt();
    pointPlus = data[2].mid(7).toInt();

    for(int y = 3; y < data.size(); y++) {
        QList<Block*> list;							//The blocks in the current row
        for(int x = 0; x < data[y].length(); x++) {
            QChar type = data[y][x];
            if(type == 'b') {						//If the character represents a block
                list << new Block(this, x * Entity::SIZE, (y - 3) * Entity::SIZE);
            } else if(type == 'p') {				//If the character represents the player
                list << nullptr;
                player = new Player(this, x * Entity::SIZE, (y - 3) * Entity::SIZE);
            } else if(type == 'x') {
                list << nullptr;					//If the character is an exit
                exit = new Exit(this, x * Entity::SIZE, (y - 3) * Entity::SIZE);
            } else if(type == 'c') {
                list << nullptr;
                Collectible* c = new Collectible(this, x * Entity::SIZE, (y - 3) * Entity::SIZE);
                entities << c;
            } else if(type == 'm') {
                PlaceableBlock* b = new PlaceableBlock(this, x * Entity::SIZE, (y - 3) * Entity::SIZE);
                list << b;
            } else if(type == 'e') {
                list << nullptr;
                Enemy* e = new Enemy(this, x * Entity::SIZE, (y - 3) * Entity::SIZE);
                entities << e;
            } else if(type == ' ') {				//If it is an empty space
                list << nullptr;
            }
        }
        blocks << list;								//Store the current row of blocks into the block list
    }
}

PlaceableBlock* Level::placeBlock(int x, int y) {
    PlaceableBlock* block = new PlaceableBlock(this, x * Entity::SIZE, y * Entity::SIZE);
    Sound::instance().placeBlock();
    blocks[y][x] = block;
    return block;
}

PlaceableBlock* Level::placeBlock(){
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
            PlaceableBlock* b = new PlaceableBlock(this, x * Entity::SIZE, y * Entity::SIZE);
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
                Sound::instance().placeBlock();
                Network::instance().send("Block " + QString::number(x) + " " + QString::number(y));
                blocks[y][x] = b;
                b->setCreating(true);
                numBlocks--;
                return b;
            } else {
                delete b;
                return nullptr;
            }
        }
    } 
    return nullptr;
}

PlaceableBlock* Level::removeBlockX(){
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

    if(blocks[y][x] != nullptr){
        PlaceableBlock* test = dynamic_cast<PlaceableBlock*>(blocks[y][x]);
        if(test != nullptr && !test->isCreating() && !test->isDeleting()) {
            Sound::instance().removeBlock();
            Network::instance().send("Remove " + QString::number(x) + " " + QString::number(y));
            test->setDeleting(true);
            numBlocks++;
        }
     }
     return nullptr;
 }

void Level::save(QTextStream &out) {
    out << "Score " << ScoreManager::instance().getCurScore() << "\n";
    out << "Numblocks " << numBlocks << "\n";

    player->savePosition(out);

    for(int i = 0; i < entities.size(); i++) {
        entities[i]->savePosition(out);
    }

    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            if(blocks[y][x]) blocks[y][x]->savePosition(out);
        }
    }
}
