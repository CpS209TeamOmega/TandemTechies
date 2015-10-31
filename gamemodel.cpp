//**********************************************************
// File: gamemodel.cpp
// Desc: The implementation of the class that manages the game
//**********************************************************

#include "gamemodel.h"
#include <QFile>
#include <QDebug>
#include <QList>

GameModel::GameModel()
{
    levelDataFile = ":/levels.dat";
    currentLevel = 0;
}

void GameModel::update()
{
	//Update the level that the user is currently playing
    levels[currentLevel]->update();

	//Test to see if the user has gotten to the exit
    if(levels[currentLevel]->isFinished()) {
        levels[currentLevel]->setFinished(false);

		//Go the the next level and make sure the currentLevel is not the last level
        currentLevel++;		
        if(currentLevel >= levels.size()) {
            currentLevel = 0;
            resetGame();
        }
        updateGUI = true;
    }
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
    int numberBlocks = 0;       //Number of moveable blocks
    QString levelName;          //The name of the level

    QTextStream in(&loadFile);  //To read the text in the file
    while(!in.atEnd()) {        //Read until end of file
        QString line = in.readLine();

        if(line.startsWith("level")) { //Start a new level and get the level's name
            levelName = line.mid(6);
        } else if(line.startsWith("blocks")) { //How many moveable blocks are in the file
            numberBlocks = line.mid(7).toInt();
        } else if(line.startsWith("endlevel")) { //Creates the level
            Level* level = new Level(levelData);
            level->setNumBlocks(numberBlocks);
            level->setName(levelName);
            levels << level;                     //Store the level in the gamemodel's list

            levelData.clear();                   //Get ready for reading another level
        } else if(!line.isEmpty()) {
            levelData << line;
        }
    }

    return true;
}

GameModel::~GameModel() {
    for(int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
}

Block* GameModel::placeBlock() {
    if(getCurrentLevel()->getPlayer()->isLeft()){
        return getCurrentLevel()->placeBlock(getCurrentLevel()->getPlayer()->getX() - Entity::SIZE, getCurrentLevel()->getPlayer()->getY());
    } else {
        return getCurrentLevel()->placeBlock(getCurrentLevel()->getPlayer()->getX() + Entity::SIZE * 2, getCurrentLevel()->getPlayer()->getY());
    }
    return nullptr;
}

void GameModel::playerInputP(int p){//Press Event Handler
    switch (p){
    case Qt::Key_Up:
        getCurrentLevel()->getPlayer()->setJumping(true);
        break;
    case Qt::Key_Left:
        getCurrentLevel()->getPlayer()->setLeft(true);
        getCurrentLevel()->getPlayer()->setFace(true);
        break;
    case Qt::Key_Right:
        getCurrentLevel()->getPlayer()->setRight(true);
        getCurrentLevel()->getPlayer()->setFace(false);
        break;
    default:

        break;
    }
}


void GameModel::playerInputR(int r){//Release Event Handler
    switch (r){
    case Qt::Key_Up:
        getCurrentLevel()->getPlayer()->setJumping(false);
        break;
    case Qt::Key_Left:
        getCurrentLevel()->getPlayer()->setLeft(false);
        break;
    case Qt::Key_Right:
        getCurrentLevel()->getPlayer()->setRight(false);
        break;
    default:

        break;
    }
}
