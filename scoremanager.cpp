//**********************************************************
// File: scoremanager.cpp
// Desc: The implementation of the score manager
//**********************************************************

#include "scoremanager.h"

#include <QtSql/QSqlDatabase>
#include <QDebug>

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

void ScoreManager::update()
{
    buddy->setText(QString::number(curScore));
}

int ScoreManager::addToScore(int plusScore)
{
    curScore += plusScore;
    buddy->setText(QString::number(curScore));
    return curScore;
}

bool ScoreManager::addHighScore(QString player, int score)
{
    //after game has ended.....
    dashBoard.insert(player, score);
    return 0;
}

void ScoreManager::saveScores()
{
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not save scores!";
        return;
    }

    //loops through all the current scores and stores them in the file
    QHash<QString, int>::const_iterator i = dashBoard.constBegin();
    QTextStream out(&file);
    while (i != dashBoard.constEnd())
    {
        out << i.key() << ": " << i.value() << "\n";
    }
}

void ScoreManager::loadScores()
{
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not load scores!";
        return;
    }
    else
    {
        QTextStream in(&file);
        QString line = in.readLine();
        while(!line.isNull())
        {
            line = in.readLine();
        }
    }
}

//singleton
ScoreManager* ScoreManager::instance_ = nullptr;

ScoreManager& ScoreManager::instance()
{
    if(instance_ == nullptr)
    {
        instance_ = new ScoreManager();
    }
    return *instance_;
}
