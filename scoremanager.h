#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

//I don't know how to use QHash things.....
#include <QHash>
#include <QDebug>
#include <QString>

class ScoreManager
{
private:
    QString fileName = "scores.dat"; //The file to save the scores to
    QHash<QString, int> dashBoard;   //The virtual score "dashboard"

    int curScore;                    //The current score in-game
    int highScore;                   //The highest score  
    int scorePlus;                   //amount added to curScore when something happens

public:
    ScoreManager();

    //return the highest score ever
    int getHiScore();

    //return the records of scores and players
    QHash<QString, int> getAllScores() { return dashBoard; }

    //Saves the scores to the file
    void saveScores();

    //Loads all of the scores from file
    void loadScores();

    //Adds a score to the list of high scores
    bool addScore(QString player, int score);//Add to scoreTable and update dashBoard

    //getters
    int getScore() { return currentScore; }
    QHash<QString, int> getScores() { return dashBoard; }

    //setters
    void setScore(int newScore) { curScore = newScore; }
};

#endif // SCOREMANAGER_H
