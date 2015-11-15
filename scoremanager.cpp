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

void ScoreManager::addHighScore(QString player, int score)
{
    dashBoard.insert(player, score);

    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not open file.";
        return;
    }
    else
    {
        QTextStream out(&file);
//        QString line = out.readLine();
//        while(!line.isNull())
//        {
//            line = out.readLine();
//            out << line;
//        }
        out << player << ": " << score << "\n";
    }
}

void ScoreManager::writeScores()
{
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not write scores!";
        return;
    }
    else
    {
        //loops through all the current scores and stores them in the file
        QHash<QString, int>::const_iterator i = dashBoard.constBegin();
        QTextStream out(&file);
        while (i != dashBoard.constEnd())
        {
            out << i.key() << ": " << i.value() << "\n";
        }
    }
}

QString ScoreManager::readScores()
{
    QString line;
    if(!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not read scores!";
        return 0;
    }
    else
    {
        QTextStream in(&file);
        line = in.readLine();
        while(!line.isNull())
        {
            line = in.readLine();
        }
    }
    return line;
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
