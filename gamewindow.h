//**********************************************************
// File: gamewindow.h
// Desc: The main window's header file
//**********************************************************

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "gamemodel.h"

#include "gamemodel.h"
#include "menu.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

    GameModel model;
    Menu menu;

    int fps = 20;


public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    static int WIDTH;       //The width of the window
    static int HEIGHT;      //The height of the window

public slots:
    void timerHit();        //When the timer goes off for the next frame update

private:
    Ui::GameWindow *ui;

private slots:
    void start();
    void load();
    void exit();
    void keyPressEvent(QKeyEvent *k);
    void keyReleaseEvent(QKeyEvent *k);

};

#endif // GAMEWINDOW_H
