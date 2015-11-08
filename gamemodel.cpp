//**********************************************************
// File: gamemodel.cpp
// Desc: The implementation of the class that manages the game
//**********************************************************

#include "gamemodel.h"
#include "enemy.h"
#include "network.h"
#include <QFile>
#include <QDebug>
#include <QList>

GameModel::GameModel()
{
    levelDataFile = ":/levels.dat";
    currentLevel = 0;
    updateGUI = false;
}

void GameModel::update()
{
	//Update the level that the user is currently playing
    getCurrentLevel()->update();

    //If the player is dead, then reset the level and decrement the lives
    if(getCurrentLevel()->getPlayer()->isDead()) {
        getCurrentLevel()->getPlayer()->setDead(false);
        getCurrentLevel()->getPlayer()->setLives(getCurrentLevel()->getPlayer()->getLives() - 1);
        Network::instance().send("Reset");
        resetCurrentLevel();
        updateGUI = true;
    }

	//Test to see if the user has gotten to the exit
    if(getCurrentLevel()->isFinished()) {
        if(Network::instance().isOpen()) { Network::instance().write("Finished\n"); }

        levelFinished();
    }

    //Update the background image
    double width = getCurrentLevel()->getBlocks()[0].size() * Entity::SIZE;
    double height = getCurrentLevel()->getBlocks().size() * Entity::SIZE;
    double pX = getCurrentLevel()->getPlayer()->getX();
    double pY = getCurrentLevel()->getPlayer()->getY();
    back->move(-(pX / width * 250), -(pY / height) * 25);
}

void GameModel::levelFinished() {
    //Go the the next level and make sure the currentLevel is not the last level
    ScoreManager::instance().addToScore(getCurrentLevel()->getPoints());
    currentLevel++;
    if(currentLevel >= levels.size()) {
        currentLevel = 0;
        resetGame();
    }
    getCurrentLevel()->load();
    updateGUI = true;
}

void GameModel::resetGame() {
    for(int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
    levels.clear();
    loadLevels();
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

void GameModel::resetCurrentLevel() {
    Level* level = getCurrentLevel();
    ScoreManager::instance().setScore(level->getScoreBeforeLevel());
    ScoreManager::instance().update();
    QList<QString> data = level->getData();
    Level* newLevel = new Level(data, this);
    levels.removeOne(level);
    delete level;
    levels.insert(currentLevel, newLevel);
    newLevel->load();
}

GameModel::~GameModel() {
    for(int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
}

PlaceableBlock* GameModel::placeBlock() {
    return getCurrentLevel()->placeBlock();
}

PlaceableBlock* GameModel::placeBlock(int x, int y) {
    return getCurrentLevel()->placeBlock(x, y);
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
