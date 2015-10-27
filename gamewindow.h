//**********************************************************
// File: gamewindow.h
// Desc: The main window's header file
//**********************************************************

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

    GameModel model;        //So we can access the framework or model of the game
    int fps = 20;           //The frames per second of the game - it is very low
                            //    because we are not using the graphics card

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    static int WIDTH;       //The width of the window
    static int HEIGHT;      //The height of the window

public slots:
    void timerHit();        //When the timer goes off for the next frame update

private:
    Ui::GameWindow *ui;
};

#endif // GAMEWINDOW_H
