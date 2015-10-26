#include "scoremanager.h"
#include <QtSql/QSqlDatabase>

ScoreManager::ScoreManager()
{
    curScore = 0;
    highScore = 0;
}

int ScoreManager::getHiScore()
{
    highScore = dashBoard.value(0);
    for(int i = 0; i < dashBoard.size() - 1; i++)
    {
        if(dashBoard.value(i) > highScore)
        {
            highScore = dashBoard.value(i);
        }
    }
    return highScore;
}

void ScoreManager::saveScores()
{
    //loops through all the current scores and stores them in the file
    for(int i = 0; i < dashBoard.size() - 1; i++)
    {
        filename << dashBoard.key() << ": " << dashBoard.value() << endl;
    }
}

void ScoreManager::loadScores()
{
    for(int i = 0; i < dashBoard.size() - 1; i++)
    {
        //output stuff
    }
}

bool ScoreManager::addScore(QString player, int score)
{
    //after game has ended.....
    dashBoard.insert(player, score);
}
