//**********************************************************
// File: gamewindow.cpp
// Desc: The main window of the entire game - for the actual
//          graphics and such of the game
//**********************************************************

#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QObjectList>
#include <QKeyEvent>

//The default width of the game
int GameWindow::WIDTH = 1024;

//The default height
int GameWindow::HEIGHT = 768;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    setFixedSize(WIDTH, HEIGHT);
    fps = 60;

    //Connect slots with signal from Menu
    QObject::connect(&menu, SIGNAL(startGame()), this, SLOT(start()));
    QObject::connect(&menu, SIGNAL(loadGame()), this, SLOT(load()));
    QObject::connect(&menu, SIGNAL(exitGame()), this, SLOT(exit()));

    blockImg.load(":/images/block.png");
    playerImg.load(":/images/player.png");
    exitImg.load(":/images/exit.png");

    if(!model.loadLevels()) {
        qDebug() << "Couldn't load the levels!";
        exit();
    } else {
         updateGUI();

         QTimer *timer = new QTimer(this);
         timer->setInterval(1000 / fps);
         connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
         timer->start();
    }
}

void GameWindow::makeLabel(Entity* e, QPixmap image) {
    QLabel* lbl = new QLabel(this);
    lbl->setGeometry(e->getRect());
    lbl->setPixmap(image);
    lbl->setScaledContents(true);
    e->setBuddy(lbl);
    lbl->show();
}

void GameWindow::updateGUI() {
    QObjectList objects = children();
    for(QObject* object : objects) {
        QLabel* lbl = dynamic_cast<QLabel*>(object);
        if(lbl != nullptr) {
            lbl->deleteLater();
        }
    }

    Level* lvl = model.getCurrentLevel();

    auto blocks = lvl->getBlocks();
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            if(blocks[y][x] != nullptr) {
                  Block* b = blocks[y][x];
                  makeLabel(b, blockImg);
            }
        }
    }

    Player* p = lvl->getPlayer();
    makeLabel(p, playerImg);

    Exit* e = lvl->getExit();
    makeLabel(e, exitImg);
}

void GameWindow::timerHit() {
    model.update();
    if(model.mustUpdateGUI()) {
        updateGUI();
        model.setUpdateGUI(false);
    }
}

GameWindow::~GameWindow()
{
    delete ui;
}

//Menu Signal Receiver
void GameWindow::start(){
    qDebug() << "start signal received";
    this->show();
}

void GameWindow::load(){
    qDebug() << "load signal received";
    this->show();
}

void GameWindow::exit(){
    qDebug() << "exit signal received";
    this->close();
}

//Key Event
//<k>The key player pressed/released
void GameWindow::keyPressEvent(QKeyEvent *k){
    if (k->key() == Qt::Key_Escape) this->close();
    model.playerInputP(k->key());
}

void GameWindow::keyReleaseEvent(QKeyEvent *k){
    model.playerInputR(k->key());
}
