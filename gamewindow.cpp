#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QLabel>
#include <QDebug>
#include <QObject>

#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    setFixedSize(1024, 768);

    QObject::connect(&menu, SIGNAL(startGame()), this, SLOT(start()));
    QObject::connect(&menu, SIGNAL(loadGame()), this, SLOT(load()));
    QObject::connect(&menu, SIGNAL(exitGame()), this, SLOT(exit()));



    if(!model.loadLevels()) {
        qDebug() << "Couldn't load the levels!";
        deleteLater();
    } else {
         QPixmap blockPic(":/images/block.png");
         auto blocks = model.getCurrentLevel()->getBlocks();
         for(int y = 0; y < blocks.size(); y++) {
             for(int x = 0; x < blocks[y].size(); x++) {
                 if(blocks[y][x] != nullptr) {
                       Block* b = blocks[y][x];
                       QLabel* lbl = new QLabel(this);
                       lbl->setGeometry(b->getX(), b->getY(), b->getWidth(), b->getHeight());
                       lbl->setPixmap(blockPic);
                       lbl->setScaledContents(true);
                       lbl->show();
                 }
             }
         }

         Player p = model.getCurrentLevel()->getPlayer();
         QLabel* plbl = new QLabel(this);
         plbl->setGeometry(p.getX(), p.getY(), p.getWidth(), p.getHeight());
         QPixmap playerPic(":/images/player.png");
         plbl->setPixmap(playerPic);
         plbl->setScaledContents(true);
         plbl->show();
    }

    menu.show();

}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::start(){
    qDebug() << "start signal recieved";
    this->show();
}

void GameWindow::load(){
    qDebug() << "load signal recieved";
    this->show();
}

void GameWindow::exit(){
    qDebug() << "exit signal recieved";
    this->close();
}

void GameWindow::keyPressEvent(QKeyEvent *k){
    model.playerInputP(k->key());
}

void GameWindow::keyReleaseEvent(QKeyEvent *k){
    model.playerInputR(k->key());
}
