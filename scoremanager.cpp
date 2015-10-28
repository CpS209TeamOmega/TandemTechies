//**********************************************************
// File: scoremanager.cpp
// Desc: The implementation of the score manager
//**********************************************************

#include "scoremanager.h"

#include <QtSql/QSqlDatabase>
#include <QFile>
#include <QDebug>


ScoreManager::ScoreManager()
{
    curScore = 0;
}

int ScoreManager::getHiScore()
{
    int highScore = 0;
    QHash<QString, int>::const_iterator i = dashBoard.constBegin();
    while (i != dashBoard.constEnd())
    {
        if(highScore < i.value())
        {
            highScore = i.value();
            i++;
        }
        else
        {
            i++;
        }
    }
    return highScore;
}

void ScoreManager::saveScores()
{
    //create file to save information to
    QFile saveFile(fileName);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not save scores!";
        return;
    }

    //loops through all the current scores and stores them in the file
    QHash<QString, int>::const_iterator i = dashBoard.constBegin();
    QTextStream out(&saveFile);
    while (i != dashBoard.constEnd())
    {
        out << i.key() << ": " << i.value();
    }
}

void ScoreManager::loadScores()
{
    QFile saveFile(fileName);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not load scores!";
        return;
    }
    else
    {
        QTextStream in(&saveFile);
        QString line = in.readLine();
        while(!line.isNull())
        {
            line = in.readLine();
        }
    }
}

bool ScoreManager::addScore(QString player, int score)
{
    //after game has ended.....
    dashBoard.insert(player, score);
    return 0;
}
