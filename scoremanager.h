#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QHash>
#include <QDebug>
#include <QString>

class ScoreManager
{
private:
    QHash<QString, int> dashBoard;
    int hiScore;

public:
    ScoreManager();//create database, set everything, check open

    int getHiScore();//return the highest score ever
    QHash<QString, int> getTable();//return the records of scores and players(hashtable)

    bool addScore(QString player, int score);//Add to scoreTable and update dashBoard
};

#endif // SCOREMANAGER_H
