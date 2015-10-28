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
    QFile saveFile(filename);
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qDebug() << "Could not save high scores!";
        return;
    }

    //loops through all the current scores and stores them in the file
    QHash<QString, int>::const_iterator i = dashBoard.constBegin();
    while (i != dashBoard.constEnd())
    {
        saveFile << i.key() << ": " << i.value();
    }
}

void ScoreManager::loadScores()
{
    QHash<QString, int>::const_iterator i = dashBoard.constBegin();
    while (i != dashBoard.constEnd())
    {
        //output junk
    }
}

bool ScoreManager::addScore(QString player, int score)
{
    //after game has ended.....
    dashBoard.insert(player, score);
    return 0;
}
