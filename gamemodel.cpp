#include "gamemodel.h"
#include <QFile>
#include <QDebug>
#include <QList>

GameModel::GameModel()
{
    levelDataFile = ":/levels.dat";
    currentLevel = 0;
}

void GameModel::update() {
    levels[currentLevel]->update();
}

bool GameModel::loadLevels() {
    QFile loadFile(levelDataFile);
    if(!loadFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    QList<QString> levelData;
    int numberBlocks;
    QString levelName;

    QTextStream in(&loadFile);
    while(!in.atEnd()) {
        QString line = in.readLine();

        if(line.startsWith("level")) {
            levelName = line.mid(6);
        } else if(line.startsWith("blocks")) {
            numberBlocks = line.mid(7).toInt();
        } else if(line.startsWith("endlevel")) {
            Level* level = new Level(levelData);
            level->setNumBlocks(numberBlocks);
            level->setName(levelName);
            levels << level;

            levelData.clear();
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

void GameModel::playerInputP(int p){
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


void GameModel::playerInputR(int r){
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
}
