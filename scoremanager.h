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
#include <QLabel>
#include <QFile>

#include "block.h"
#include "collectible.h"

class ScoreManager
{
private:
    //The file to save the scores to
    QFile file;

    //The virtual score "dashboard"
    QHash<QString, int> dashBoard;

    QLabel *buddy;

    //the in-game score
    int curScore;

    //private constructor
    ScoreManager() : file("scores.txt"), curScore{0} { }

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

    //Updates the label on the screen
    void update();

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
