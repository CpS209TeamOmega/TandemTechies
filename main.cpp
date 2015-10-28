//**********************************************************
// File: main.cpp
// Desc: The entry point to the entire program
//**********************************************************

#include "gamewindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.show();

    return a.exec();
}
