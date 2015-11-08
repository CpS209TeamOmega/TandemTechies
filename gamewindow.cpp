//**********************************************************
// File: gamewindow.cpp
// Desc: The main window of the entire game - for the actual
//          graphics and such of the game
//**********************************************************

#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "enemy.h"
#include "remoteplayer.h"
#include "network.h"
#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QObjectList>
#include <QMessageBox>
#include <QKeyEvent>
#include <QtGlobal>
#include <QStringList>
#include <QIcon>

//The default width of the game
int GameWindow::WIDTH = 1024;

//The default height
int GameWindow::HEIGHT = 768;

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::GameWindow) {
    ui->setupUi(this);

    otherPlayer = nullptr;

    QIcon windowIcon(":/images/player.png");
    setWindowIcon(windowIcon);
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("Tandem Techies");
    fps = 60;

    menu = new Menu();
    menu->show();
    multiPlayer = false;

    //Connect slots with signal from Menu
    connect(menu, SIGNAL(startGame(QString)), this, SLOT(start(QString)));
    connect(menu, SIGNAL(loadGame()), this, SLOT(load()));
    connect(menu, SIGNAL(exitGame()), this, SLOT(exit()));

    //Connect server signals
    Network::instance();
    connect(Network::pointer(), SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(Network::pointer(), SIGNAL(connected()), this, SLOT(connectionSucceeded()));
    connect(Network::pointer(), SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
    connect(Network::pointer(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    Q_ASSERT(blockImg.load(":/images/block.png"));
    Q_ASSERT(exitImg.load(":/images/exit.png"));
    Q_ASSERT(collectibleImg.load(":/images/collectible.png"));
    Q_ASSERT(placeableImg.load(":/images/placeable.png"));
    Q_ASSERT(heartImg.load(":/images/heart.png"));

    if(!model.loadLevels()) {
        qDebug() << "Couldn't load the levels!";
        exit();
	} else {
        unitTests();
        updateGUI();

		QTimer *timer = new QTimer(this);
		timer->setInterval(1000 / fps);
		connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
		timer->start();
    }

    ScoreManager::instance().setBuddy(ui->lblScore);
    ui->wgStatusBar->setParent(this);
    ui->wgStatusBar->move(20, HEIGHT - 20 - ui->wgStatusBar->geometry().height());
}

void GameWindow::unitTests() {
    Level* level = model.getCurrentLevel();

    //Make sure the level's name is as it shows in levels.dat
    Q_ASSERT(level->getName() == "Beginning Your Journey");

    //Make sure the number of placeable blocks reflects levels.dat
    Q_ASSERT(level->getNumBlocks() == 0);

    //Make sure the level loaded correctly - level height == 5
    Q_ASSERT(level->getBlocks().size() == 5);

    //Make sure the level loaded correctly - level width == 8
    Q_ASSERT(level->getBlocks()[0].size() == 8);

    //Make sure the player's x position in the level is 64
    Q_ASSERT(level->getPlayer()->getX() == 64);

    //Make sure the player's y position in the level is 320
    Q_ASSERT(level->getPlayer()->getY() == 192);

    //All unit tests passed! Now on to play this amazing game!
}

void GameWindow::makeLabel(Entity* e, QPixmap image) {
    QLabel* lbl = new QLabel(this);			//Create the label
    lbl->setGeometry(e->getRect());			//Sets the geometry to reflect the entity
    lbl->setPixmap(image);					//Sets the picture of the label
    lbl->setScaledContents(true);			//Makes the picture scale to the label's size
    lbl->setAttribute(Qt::WA_TranslucentBackground);
    e->setBuddy(lbl);						//Sets the Entity's corresponding label
    lbl->show();
}

void GameWindow::updateGUI() {
    //Clear all of the current labels from the window
    QObjectList objects = children();
    for(QObject* object : objects) {
        QLabel* lbl = dynamic_cast<QLabel*>(object);
        if(lbl) { lbl->deleteLater(); }
    }

    //Get the current level
    Level* lvl = model.getCurrentLevel();

    //Create the player's label
    Player* p = lvl->getPlayer();
    makeLabel(p, QPixmap());

    auto entities = lvl->getEntities();
    for(int i = 0; i < entities.size(); i++) {
        Collectible* c = dynamic_cast<Collectible*>(entities[i]);
        if(c) { makeLabel(entities[i], collectibleImg); continue; }

        Enemy* e = dynamic_cast<Enemy*>(entities[i]);
        if(e) { makeLabel(entities[i], QPixmap()); continue; }
    }

    //Create the labels for the blocks in the level
    auto blocks = lvl->getBlocks();
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            if(blocks[y][x]) {
                  Block* b = blocks[y][x];

                  PlaceableBlock* test = dynamic_cast<PlaceableBlock*>(b);
                  if(test) {
                      makeLabel(b, placeableImg);
                      b->getBuddy()->setGeometry(b->getX(), b->getY(), 0, 0);
                  } else {
                      makeLabel(b, blockImg);
                  }
            }
        }
    }

    //Create the exit's label
    Exit* e = lvl->getExit();
    makeLabel(e, exitImg);

    if(otherPlayer) {
        otherPlayer = new RemotePlayer(lvl, 0, 0);
        makeLabel(otherPlayer, QPixmap());
        lvl->setRemotePlayer(otherPlayer);
    }

    lvl->update();

    showLives();

    model.setBackground(ui->lblBack);
    ui->lblNumBlocks->setText(QString::number(lvl->getNumBlocks()));
    ui->lblLvl->setText("Level " + QString::number(model.getLevelNumber()) + ":");
    ui->lblName->setText(lvl->getName());
    ui->wgStatusBar->raise();
}

void GameWindow::showLives() {
    QObjectList list = ui->wgLives->children();
    for(QObject* obj : list) {
        QLabel* lbl = dynamic_cast<QLabel*>(obj);
        if(lbl) lbl->deleteLater();
    }

    int margin = 10;
    int size = 32;
    for(int i = 0; i < model.getCurrentLevel()->getPlayer()->getLives(); i++) {
        QLabel* life = new QLabel(ui->wgLives);
        life->setGeometry(margin * (i + 1) + size * i, margin, size, size);
        life->setPixmap(heartImg);
        life->setScaledContents(true);
        life->show();
    }
}

void GameWindow::timerHit() {
    if(model.mustUpdateGUI()) {
        updateGUI();
        model.setUpdateGUI(false);
    }
    model.update();
    if(otherPlayer) otherPlayer->update();
}

GameWindow::~GameWindow()
{
    delete ui;
}

//Menu Signal Receiver
void GameWindow::start(QString server) {
    if(server != "") {
        Network::instance().connectToHost(server, 5000);
        Network::instance().waitForConnected();
    }
}

void GameWindow::load(){

}

void GameWindow::exit(){
    close();
}

//Key Event
//<k>The key player pressed/released
void GameWindow::keyPressEvent(QKeyEvent *k){
    if(k->key() == Qt::Key_Space) {
        PlaceableBlock* newBlock = model.placeBlock();
        if(newBlock != nullptr) {
            makeLabel(newBlock, placeableImg);
            newBlock->update();
        }
        ui->lblNumBlocks->setText(QString::number(model.getCurrentLevel()->getNumBlocks()));
    } else if (k->key() == Qt::Key_Escape) {
        menu->show();
    } else {
         model.playerInputP(k->key());
    }
}

void GameWindow::focusOutEvent(QFocusEvent *) {
    model.getCurrentLevel()->getPlayer()->clearFlags();
}

void GameWindow::leaveEvent(QEvent *) {
    model.getCurrentLevel()->getPlayer()->clearFlags();
}

void GameWindow::keyReleaseEvent(QKeyEvent *k){
    if(k->key() == Qt::Key_R) {
        model.resetCurrentLevel();
        updateGUI();
    } else {
        model.playerInputR(k->key());
    }
}

void GameWindow::connectionSucceeded() {
    multiPlayer = true;
}

void GameWindow::dataReceived() {
    //In the format [x] [y] [dir]
    QTcpSocket *sock = dynamic_cast<QTcpSocket*>(sender());
    while(sock->canReadLine()) {
        QString data = sock->readLine();
        data.chop(1);
        if(data == "Connect") {
            otherPlayer = new RemotePlayer(model.getCurrentLevel(), 0, 0);
            model.getCurrentLevel()->setRemotePlayer(otherPlayer);
            QTimer* networkTimer = new QTimer(this);
            networkTimer->setInterval(1000 / 20);
            connect(networkTimer, SIGNAL(timeout()), this, SLOT(networkTimerHit()));
            networkTimer->start();
            updateGUI();
        } else if(data == "Finished") {
            model.levelFinished();
        } else if(data.startsWith("Collectible")) {
            QStringList list = data.split(" ");
            int x = list.at(1).toInt();
            int y = list.at(2).toInt();
            QList<Entity*> entities = model.getCurrentLevel()->getEntities();
            for(int i = 0; i < entities.size(); i++) {
                if(Collectible* c = dynamic_cast<Collectible*>(entities[i])) {
                    if(c->getX() == x && c->getY() == y) {
                        c->getBuddy()->deleteLater();
                        model.getCurrentLevel()->removeEntity(c);
                        break;
                    }
                }
            }
        } else if(data.startsWith("Remove")) {
            QStringList list = data.split(" ");
            int x = list.at(1).toInt();
            int y = list.at(2).toInt();
            if(PlaceableBlock* b = dynamic_cast<PlaceableBlock*>(model.getCurrentLevel()->getBlocks()[y][x])) {
                b->setDeleting(true);
            }
        } else if(data.startsWith("Block")) {
            QStringList list = data.split(" ");
            int x = list.at(1).toInt();
            int y = list.at(2).toInt();
            PlaceableBlock* block = model.placeBlock(x, y);
            makeLabel(block, placeableImg);
            block->update();
        } else {
            otherPlayer->dataReceived(data);
        }
    }
}

void GameWindow::networkTimerHit() {
    Player* p = model.getCurrentLevel()->getPlayer();
    int x = p->getX();
    int y = p->getY();
    int dir = p->getDir();
    Network::instance().send(QString::number(x) + " " + QString::number(y) + " " + QString::number(dir));
}

void GameWindow::serverDisconnected() {
    QMessageBox::information(this, "End of the World!", "AHHHHHH THE SERVER DISCONNECTED!!! :(");
    menu->show();
}

void GameWindow::socketError(QAbstractSocket::SocketError) {

}
