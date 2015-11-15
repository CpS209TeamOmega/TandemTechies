#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include "menu.h"
#include "gamewindow.h"
#include "scoremanager.h"

#include <QWidget>
#include <QLabel>

namespace Ui {
class ScoreDisplay;
}

class ScoreDisplay : public QWidget
{
    Q_OBJECT

    Menu *menu;
    GameWindow *game;

    QLabel *scoreText;

public:
    explicit ScoreDisplay(QWidget *parent = 0);
    ~ScoreDisplay();

private:
    Ui::ScoreDisplay *ui;

private slots:
    void displayScores();
};

#endif // SCOREDISPLAY_H
