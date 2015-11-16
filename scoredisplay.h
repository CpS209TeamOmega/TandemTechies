#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include "scoremanager.h"

#include <QWidget>
#include <QLabel>

namespace Ui {
class ScoreDisplay;
}

class ScoreDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreDisplay(QWidget *parent = 0);
    ~ScoreDisplay();

    void update();

private slots:
    void on_btnDone_clicked();

    void on_btnClear_clicked();

private:
    Ui::ScoreDisplay *ui;
};

#endif // SCOREDISPLAY_H
