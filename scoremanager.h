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
    //The highest score
    int highScore;

public:
    ScoreManager();

    //return the highest score ever
    int getHiScore();

    //Saves the scores to the file
    void saveScores();

    //Loads all of the scores from file
    void loadScores();

    //Adds a score to the list of high scores
    bool addScore(QString player, int score);

    //getters
    int getCurScore() { return curScore; }
    QHash<QString, int> getScores() { return dashBoard; }

    //setters
    void setScore(int newScore) { curScore = newScore; }
};

#endif // SCOREMANAGER_H
