#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <QWidget>

#include "scoremanager.h"
#include "gamewindow.h"
#include "menu.h"

namespace Ui {
class ScoreDisplay;
}

class ScoreDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreDisplay(QWidget *parent = 0);
    ~ScoreDisplay();

private:
    Ui::ScoreDisplay *ui;
};

#endif // SCOREDISPLAY_H
