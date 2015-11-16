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
#include <QTcpSocket>

#include "gamemodel.h"
#include "remoteplayer.h"
#include "entity.h"
#include "menu.h"
#include "scoremanager.h"
#include "scoredisplay.h"

namespace Ui
{
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

    GameModel model;          //For the GUI/model interactions
    Menu* menu;               //The Game menu
    ScoreDisplay* display;
    RemotePlayer* otherPlayer;
    bool multiPlayer;

    //All of the images for the game
    QPixmap blockImg;
    QPixmap collectibleImg;
    QPixmap exitImg;
	QPixmap placeableImg;
    QPixmap heartImg;
    QPixmap bulletImg;
    QPixmap bulletImgR;
    QPixmap cBulletImg;
    QPixmap cBulletImgR;

    int fps;                //The frames per second the game will run at


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

    //Adds the hearts to the status bar label for how
    //many lives the player has left
    void showLives();

    //Save the state of the game for loading next time
    void save();

    //Make sure the check is true. If not, terminate program.
    void check(bool val);

    static int WIDTH;       //The width of the window
    static int HEIGHT;      //The height of the window

private:
    Ui::GameWindow *ui;

signals:
    void scores();

private slots:
    void timerHit();        //When the timer goes off for the next frame update
    void networkTimerHit();

    void start(QString server);
    void load();
    void exit();
    void endGame(bool done, bool server);
    void highScores();

    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *k);
    void keyReleaseEvent(QKeyEvent *k);
    void focusOutEvent(QFocusEvent*);
    void leaveEvent(QEvent*);

    void serverDisconnected();
    void dataReceived();
    void connectionSucceeded();
    void socketError(QAbstractSocket::SocketError error);
};

#endif // GAMEWINDOW_H
