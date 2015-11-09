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
        scoremanager.cpp \
    level.cpp \
    block.cpp \
    menu.cpp \
    exit.cpp \
    collectible.cpp \
    enemy.cpp \
    scoredisplay.cpp

HEADERS  += gamewindow.h\
        entity.h\
        gamemodel.h\
        player.h\
        scoremanager.h \
    level.h \
    block.h \
    menu.h \
    exit.h \
    collectible.h \
    enemy.h \
    scoredisplay.h

FORMS    += gamewindow.ui \
    menu.ui \
    scoreDisplay.ui

QMAKE_CXXFLAGS += -std=c++11

RESOURCES += \
    resources.qrc

DISTFILES +=
