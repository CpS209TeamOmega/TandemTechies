#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "gamemodel.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

    GameModel model;
    int fps = 20;

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    static int WIDTH;
    static int HEIGHT;

public slots:
    void timerHit();

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
