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
#include <QLabel>

#include "block.h"
#include "collectible.h"

class ScoreManager
{
private:
    //The file to save the scores to
    QString fileName;

    //The virtual score "dashboard"
    QHash<QString, int> dashBoard;

    QLabel *buddy;

    //the start score
    int startScore;

    //the in-game score
    int curScore;

    //private constructor
    ScoreManager() : startScore{0}, curScore{0} { }

public:
    //Return the highest score ever
    int getHiScore();

    //add points to the current score
    int addToScore(int plusScore);

    //<player> The player's name
    //<score> The score the player got
    bool addHighScore(QString player, int score);//Add to scoreTable and update dashBoard

    //Return the records of scores and players
    QHash<QString, int> getAllScores();

    //Saves the scores to the file
    void saveScores();

    //Loads all of the scores from file
    void loadScores();

    //getters
    int getCurScore() { return curScore; }
    QLabel* getBuddy() { return buddy; }

    //setters
    void setScore(int newScore) { curScore = newScore; }
    void setBuddy(QLabel *newBuddy) {buddy = newBuddy; }

private:
    static ScoreManager *instance_;

public:
    static ScoreManager& instance();

};

#endif // SCOREMANAGER_H
