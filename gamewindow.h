//**********************************************************
// File: gamewindow.h
// Desc: The main window's header file
//**********************************************************

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include <QWidget>
#include "gamemodel.h"
#include "entity.h"
#include "menu.h"

namespace Ui
{
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

    GameModel model;
    Menu* menu;
    QWidget* wgScore;

    QPixmap blockImg;
    QPixmap playerImg;
    QPixmap exitImg;
	QPixmap backgroundImg;

    int fps;


public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

    //Creates a label with the given entity and image
    void makeLabel(Entity* e, QPixmap image);

	//Updates the GUI to reflect the state of the level.
	//This method is called when the level is changed, e.g.
	//evel 1 to level 2
    void updateGUI();

	//Performs unit tests to make sure the game is working,
	//and exits the program if any of them fail.
	void unitTests();

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
