//**********************************************************
// File: scoremanager.h
// Desc: This class does all of the score management -
//          saving high scores, and updating the current score
//**********************************************************

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QHash>
#include <QDebug>
#include <QString>

class ScoreManager
{
private:
    QString fileName = "scores.dat"; //The file to save the scores to
    QHash<QString, int> dashBoard;   //The virtual score "dashboard"
    int currentScore;                //The current score in-game

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

    //Adds a score to the list of high scores
    //<player> The player's name
    //<score> The score the player got
    bool addScore(QString player, int score);//Add to scoreTable and update dashBoard
};

#endif // SCOREMANAGER_H
