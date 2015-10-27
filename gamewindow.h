#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
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


public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();

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
