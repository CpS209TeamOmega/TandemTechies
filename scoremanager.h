//**********************************************************
// File: scoremanager.h
// Desc: This class does all of the score management -
//          saving high scores, and updating the current score
//**********************************************************

#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include <QDebug>
#include <QString>
#include <QLabel>
#include <QFile>

#include "block.h"
#include "menu.h"
#include "collectible.h"

class ScoreManager
{
private:
    //The file to save the scores to
    QFile file;

    //The label on the screen with the score
    QLabel *buddy;

    //the in-game score
    int curScore;

    //private constructor
    ScoreManager() : file("scores.txt"), curScore(0) { }

public:

    //add points to the current score
    int addToScore(int plusScore);

    //<player> The player's name
    //<score> The score the player got
    void addHighScore(QString player);//Add to scoreTable and update dashBoard

    //Loads all of the scores from file
    QStringList readScores();

    //Updates the label on the screen
    void update();

    //Deletes all high scores
    void deleteHighScores();

    //getters
    int getCurScore() { return curScore; }
    QLabel* getBuddy() { return buddy; }

    //setters
    void setScore(int newScore) { curScore = newScore; update(); }
    void setBuddy(QLabel *newBuddy) {buddy = newBuddy; }

private:
    static ScoreManager *instance_;

public:
    static ScoreManager& instance();

};

#endif // SCOREMANAGER_H
