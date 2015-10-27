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

    //return the highest score ever
    int getHiScore();

    //return the records of scores and players
    QHash<QString, int> getAllScores();

    //Saves the scores to the file
    void saveScores();

    //Loads all of the scores from file
    void loadScores();

    //Adds a score to the list of high scores
    bool addScore(QString player, int score);//Add to scoreTable and update dashBoard
};

#endif // SCOREMANAGER_H
