#-------------------------------------------------
#
# Project created by QtCreator 2015-10-21T09:45:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TandemTechies
TEMPLATE = app


SOURCES += main.cpp\
        gamewindow.cpp\
        entity.cpp\
        gamemodel.cpp\
        player.cpp\
        scoremanager.cpp

HEADERS += gamewindow.h\
        entity.h\
        gamemodel.h\
        player.h\
        scoremanager.h

FORMS    += gamewindow.ui
