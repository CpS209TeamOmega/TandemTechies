#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QHash>
#include <QtSql/QSqlDatabase>
#include <QDebug>


class ScoreManager
{
private:
    QSqlDatabase db;
    QHash<string, int> dashBoard;
    QHash<string, int> scoreTable;
    int hiScore;

public:
    ScoreManager();//create database, set everything, check open

    int getHiScore();//return the highest score ever
    QHash<string, int> getTable();//return the records of scores and players(hashtable)

    bool addScore(string player, int score);//Add to scoreTable and update dashBoard

    bool updateDash();//called whenever addScore is called
};

#endif // SCOREMANAGER_H
