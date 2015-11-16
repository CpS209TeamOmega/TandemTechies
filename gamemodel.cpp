//**********************************************************
// File: gamemodel.cpp
// Desc: The implementation of the class that manages the game
//**********************************************************

#include "gamemodel.h"
#include "enemy.h"
#include "sound.h"
#include "network.h"
#include <QFile>
#include <QDebug>
#include <QList>

GameModel::GameModel()
{
    levelDataFile = ":/levels.dat";
    currentLevel = 0;
    updateGUI = false;
    lives = 8;
    cheating = false;
}

void GameModel::update()
{
    //Update the level that the user is currently playing
    getCurrentLevel()->update();

    //If the player is dead, then reset the level and decrement the lives
    if(getCurrentLevel()->getPlayer()->isDead()) {
        Sound::instance().gameOver();
        getCurrentLevel()->getPlayer()->setDead(false);
        lives--;
        if(lives <= 0) {
            emit gameFinished(false, false);
        }
        Network::instance().send("Reset");
        resetCurrentLevel();
        updateGUI = true;
    }

    //Test to see if the user has gotten to the exit
    if(getCurrentLevel()->isFinished()) {
        if(currentLevel + 1 < levels.size()) {
            Network::instance().send("Finished");
        }

        levelFinished();
    }

    //Update the background image
    double width = getCurrentLevel()->getBlocks()[0].size() * Entity::SIZE;
    double height = getCurrentLevel()->getBlocks().size() * Entity::SIZE;
    double pX = getCurrentLevel()->getPlayer()->getX();
    double pY = getCurrentLevel()->getPlayer()->getY();
    back->move(-(pX / width * 250) + getCurrentLevel()->getAmplitudeW(), -(pY / height) * 25 + getCurrentLevel()->getAmplitudeH());
}

Level* GameModel::getCurrentLevel() {
    if(currentLevel >= levels.size()) return nullptr;
    else return levels[currentLevel];
}

void GameModel::setCurrentLevel(int newLevel) {
    currentLevel = newLevel;
}

void GameModel::levelFinished() {
    //Go the the next level and make sure the currentLevel is not the last level
    ScoreManager::instance().addToScore(getCurrentLevel()->getPoints());
    Sound::instance().endLevel();
    currentLevel++;
    if(currentLevel >= levels.size()) {
        emit gameFinished(true, false);
        resetGame();
    }
    getCurrentLevel()->load();
    cheating = false;
    updateGUI = true;
}

void GameModel::resetGame() {
    for(int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
    cheating = false;
    currentLevel = 0;
    levels.clear();
    loadLevels();
    lives = 8;
    ScoreManager::instance().setScore(0);
}

bool GameModel::loadLevels() {
    QFile loadFile(levelDataFile); //Locates and opens the level data file
    if(!loadFile.open(QIODevice::ReadOnly)) { //Makes sure it opened
        return false;
    }

    QList<QString> levelData;   //The strings of data for the level
    QTextStream in(&loadFile);  //To read the text in the file

    while(!in.atEnd()) {        //Read until end of file
        QString line = in.readLine();
        if(line.startsWith("endlevel")) {
            levels << new Level(levelData, this);
            levelData.clear();
        } else if(!line.isEmpty()) {
            levelData << line;
        }
    }

    getCurrentLevel()->load();

    return true;
}

void GameModel::save() {
    qDebug() << "Saving Game File";
    QFile saveFile("save.dat");
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error saving game data";
        return;
    }

    QTextStream out(&saveFile);

    out << "Level " << currentLevel << "\n";
    out << "Lives " << lives << "\n";

    getCurrentLevel()->save(out);
    saveFile.close();
    qDebug() << "Game saved.";
}

bool GameModel::load() {
    QFile loadFile("save.dat");
    if(!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not load save file.";
        return false;
    }

    qDebug() << "Loading save file.";
    QTextStream in(&loadFile);

    while(!in.atEnd()) {
        QString line = in.readLine();

        if(!line.isEmpty()) {
            if(line.startsWith("Level")) { //Level number
                QStringList list = line.split(" ");
                setCurrentLevel(list[1].toInt());
                getCurrentLevel()->load();
                cheating = false;
                getCurrentLevel()->removeAllEntities();
                getCurrentLevel()->removePlaceableBlocks();                
            } else if(line.startsWith("Score")) {
                QStringList list = line.split(" ");
                ScoreManager::instance().setScore(list[1].toInt());
                ScoreManager::instance().update();
            } else if(line.startsWith("Numblocks")) {
                QStringList list = line.split(" ");
                getCurrentLevel()->setNumBlocks(list[1].toInt());
            } else if(line.startsWith("Lives")) {
                QStringList list = line.split(" ");
                lives = list[1].toInt();
            } else if(line.startsWith("Bullet")) {
                QStringList list = line.split(" ");
                bool cheat = list.at(1) == "c";
                int x = list.at(2).toInt();
                int y = list.at(3).toInt();
                int dir = list.at(4).toInt();
                Bullet* b = new Bullet(getCurrentLevel(), x, y);
                b->setDir(dir);
                b->setInvincible(cheat);
                getCurrentLevel()->getEntities() << b;
            } else if(line.startsWith("Player")) { //Player position
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                int dir = list[3].toInt();
                Player* p = new Player(getCurrentLevel(), x, y);
                p->setX(x);
                p->setY(y);
                p->setWidth(Entity::SIZE);
                p->setHeight(Entity::SIZE);
                p->setDir(dir);
                getCurrentLevel()->setPlayer(p);
            } else if(line.startsWith("Enemy")) { //Enemy position
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                int dir = list[3].toInt();
                Enemy* e = new Enemy(getCurrentLevel(), x, y);
                e->setDir(dir);
                getCurrentLevel()->getEntities() << e;
            } else if(line.startsWith("FlyingEnemy")) { //Enemy position
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                int dir = list[3].toInt();
                FlyingEnemy* e = new FlyingEnemy(getCurrentLevel(), x, y);
                e->setDir(dir);
                getCurrentLevel()->getEntities() << e;
            } else if(line.startsWith("Collect")) { //Collectibles
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                getCurrentLevel()->getEntities() << new Collectible(getCurrentLevel(), x, y);
            } else if(line.startsWith("Block")) { //Placeable Blocks
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                getCurrentLevel()->getBlocks()[y / Entity::SIZE][x / Entity::SIZE] = new PlaceableBlock(getCurrentLevel(), x, y);
            }
        }
    }
    loadFile.close();
    updateGUI = true;
    return true;
}

void GameModel::resetCurrentLevel() {
    Level* level = getCurrentLevel();
    ScoreManager::instance().setScore(level->getScoreBeforeLevel());
    QList<QString> data = level->getData();
    Level* newLevel = new Level(data, this);
    newLevel->load();
    levels.removeOne(level);
    delete level;
    cheating = false;
    levels.insert(currentLevel, newLevel);
    updateGUI = true;
}

GameModel::~GameModel() {
    for(int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
}

PlaceableBlock* GameModel::placeBlock() {
    return getCurrentLevel()->placeBlock();
}

PlaceableBlock* GameModel::removeBlock(){
    return getCurrentLevel()->removeBlockX();
}

PlaceableBlock* GameModel::placeBlock(int x, int y) {
    return getCurrentLevel()->placeBlock(x, y);
}

Bullet* GameModel::fire(){
    return getCurrentLevel()->fire();
}

void GameModel::playerInputP(int p){//Press Event Handler
    switch (p) {
    case Qt::Key_W:
    case Qt::Key_Up:
        getCurrentLevel()->getPlayer()->setJumping(true);
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        getCurrentLevel()->getPlayer()->setLeft(true);
		getCurrentLevel()->getPlayer()->setDir(-1);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        getCurrentLevel()->getPlayer()->setRight(true);
		getCurrentLevel()->getPlayer()->setDir(1);
        break;
    case Qt::Key_C:
        getCurrentLevel()->getPlayer()->setCheatJumpHeight();
        cheating = !cheating;
        break;
    default:
        break;
    }
}


void GameModel::playerInputR(int r){//Release Event Handler
    switch (r) {
    case Qt::Key_W:
    case Qt::Key_Up:
        getCurrentLevel()->getPlayer()->setJumping(false);
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        getCurrentLevel()->getPlayer()->setLeft(false);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        getCurrentLevel()->getPlayer()->setRight(false);
        break;
    default:
        break;
    }
}
