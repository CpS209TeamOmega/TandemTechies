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
    levels[currentLevel]->update();
}

bool GameModel::loadLevels() {
    QFile loadFile(levelDataFile); //Locates and opens the level data file
    if(!loadFile.open(QIODevice::ReadOnly)) { //Makes sure it opened
        return false;
    }

    QList<QString> levelData;   //The strings of data for the level
    int numberBlocks;           //Number of moveable blocks
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

void GameModel::playerInputP(int p){//Press Event Handler
    switch (p){
    case Qt::Key_Up:
        qDebug() << "U key pressed";
        break;
    case Qt::Key_Down:
        qDebug() << "D key pressed";
        break;
    case Qt::Key_Left:
        qDebug() << "L key pressed";
        break;
    case Qt::Key_Right:
        qDebug() << "R key pressed";
        break;
    default:

        break;
    }
}


void GameModel::playerInputR(int r){//Release Event Handler
    switch (r){
    case Qt::Key_Up:
        qDebug() << "U key released";
        break;
    case Qt::Key_Down:
        qDebug() << "D key released";
        break;
    case Qt::Key_Left:
        qDebug() << "L key released";
        //levels.at(currentLevel)->getPlayer().setX(levels.at(currentLevel)->getPlayer().getX()-1);

        break;
    case Qt::Key_Right:
        qDebug() << "R key released";
        break;
    default:

        break;
    }
>>>>>>> upstream/master
}
