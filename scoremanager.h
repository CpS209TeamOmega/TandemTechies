//**********************************************************
// File: scoremanager.h
// Desc: This class does all of the score management -
//          saving high scores, and updating the current score
//**********************************************************

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

//I don't know how to use QHash things.....
#include <QHash>
#include <QDebug>
#include <QString>

#include "block.h"
#include "collectibles.h"

class ScoreManager
{
private:
    //The file to save the scores to
    QString fileName;

    //The virtual score "dashboard"
    QHash<QString, int> dashBoard;

    //The current score in-game
    int curScore;

public:
    ScoreManager();

    //Return the highest score ever
    int getHiScore();

    //Return the records of scores and players
    QHash<QString, int> getAllScores();

    //Saves the scores to the file
    void saveScores();

    //Loads all of the scores from file
    void loadScores();

    //getters
    int getCurScore() { return curScore; }

    //setters
    void setScore(int newScore) { curScore = newScore; }

    //<player> The player's name
    //<score> The score the player got
    bool addScore(QString player, int score);//Add to scoreTable and update dashBoard

};

#endif // SCOREMANAGER_H
