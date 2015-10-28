//**********************************************************
// File: main.cpp
// Desc: The entry point to the entire program
//**********************************************************

#include "gamewindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    //Move window to the center of the screen
    w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
    w.show();

    return a.exec();
}
