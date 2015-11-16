//**********************************************************
// File: scoremanager.cpp
// Desc: The implementation of the score manager
//**********************************************************

#include "scoremanager.h"
#include <QDebug>

void ScoreManager::update()
{
    buddy->setText(QString::number(curScore));
}

int ScoreManager::addToScore(int plusScore)
{
    curScore += plusScore;
    buddy->setText(QString::number(curScore));
    return curScore;
}

void ScoreManager::addHighScore(QString player)
{
    if(!file.open(QIODevice::Append | QIODevice::Text))
    {
        qDebug() << "Could not open file.";
        return;
    }
    else
    {
        QTextStream out(&file);
        out << "\n" << player << ": " << curScore;
    }
    file.close();
}

void ScoreManager::deleteHighScores() {
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "Could not read score file!";
    } else {
        QTextStream out(&file);
        out << "";
    }
    file.close();
}

QStringList ScoreManager::readScores()
{
    QStringList lines;
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not read scores!";
        return lines;
    }
    else
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            lines << in.readLine();
        }
    }
    file.close();
    return lines;
}

//singleton
ScoreManager* ScoreManager::instance_ = nullptr;

ScoreManager& ScoreManager::instance()
{
    if(instance_ == nullptr)
    {
        instance_ = new ScoreManager();
    }
    return *instance_;
}
