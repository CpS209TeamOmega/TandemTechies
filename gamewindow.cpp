//**********************************************************
// File: gamewindow.cpp
// Desc: The main window of the entire game - for the actual
//          graphics and such of the game
//**********************************************************

#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "enemy.h"
#include "remoteplayer.h"
#include "scoredisplay.h"
#include "network.h"
#include "sound.h"
#include "bullet.h"

#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QObjectList>
#include <QMessageBox>
#include <QKeyEvent>
#include <QFile>
#include <QInputDialog>
#include <QtGlobal>
#include <QStringList>
#include <QIcon>
#include <QMessageBox>

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

    display = new ScoreDisplay();
    menu = new Menu();
    menu->show();
    multiPlayer = false;

    //Connect slots with signal from Menu
    connect(menu, SIGNAL(startGame(QString)), this, SLOT(start(QString)));
    connect(menu, SIGNAL(loadGame()), this, SLOT(load()));
    connect(menu, SIGNAL(exitGame()), this, SLOT(exit()));
    connect(menu, SIGNAL(highScores()), this, SLOT(highScores()));
    connect(&model, SIGNAL(gameFinished(bool)), this, SLOT(endGame(bool)));

    //Connect server signals
    Network::instance();
    connect(Network::pointer(), SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(Network::pointer(), SIGNAL(connected()), this, SLOT(connectionSucceeded()));
    connect(Network::pointer(), SIGNAL(disconnected()), this, SLOT(serverDisconnected()));
    connect(Network::pointer(), SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socketError(QAbstractSocket::SocketError)));

    check(blockImg.load(":/images/block.png"));
    check(exitImg.load(":/images/exit.png"));
    check(collectibleImg.load(":/images/collectible.png"));
    check(placeableImg.load(":/images/placeable.png"));
    check(heartImg.load(":/images/heart.png"));
    check(bulletImg.load(":/images/b_left.png"));
    check(bulletImgR.load(":/images/b_right.png"));
    check(cBulletImg.load(":/images/bc_left.png"));
    check(cBulletImgR.load(":/images/bc_right.png"));

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

void GameWindow::check(bool val) {
    if(!val) {
        qDebug() << "Error on check!";
        close();
    }
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

        FlyingEnemy* f = dynamic_cast<FlyingEnemy*>(entities[i]);
        if(f) { makeLabel(entities[i], QPixmap()); continue; }

        Bullet* b = dynamic_cast<Bullet*>(entities[i]);
        if(b) {
            QPixmap map;
            bool cheat = b->isInvincible();
            int dir = b->getDir();
            if(cheat && dir == -1) map = cBulletImg;
            else if(cheat && dir == 1) map = cBulletImgR;
            else if(dir == -1) map = bulletImg;
            else map = bulletImgR;
            makeLabel(entities[i], map);
        }
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
        otherPlayer->getBuddy()->deleteLater();
        delete otherPlayer;
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
    for(int i = 0; i < model.getLives(); i++) {
        QLabel* life = new QLabel(ui->wgLives);
        life->setGeometry(margin * (i + 1) + size * i, margin, size, size);
        life->setPixmap(heartImg);
        life->setScaledContents(true);
        life->show();
    }
}

void GameWindow::timerHit() {
        if(menu->isHidden()) {
            if(model.mustUpdateGUI()) {
                updateGUI();
                model.setUpdateGUI(false);
            }
            model.update();
            if(otherPlayer) otherPlayer->update();
        }
}

GameWindow::~GameWindow()
{
    delete ui;
    delete otherPlayer;
}

//Menu Signal Receiver
void GameWindow::start(QString server) {
    if(server != "") {
        Network::instance().connectToHost(server, 5000);
        Network::instance().waitForConnected();
    }
}

void GameWindow::load() {
    if(!model.load()) {
        qDebug() << "Could not load last save.";
    }
}

void GameWindow::exit(){
    close();
}

void GameWindow::closeEvent(QCloseEvent* e) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Save", "Save game before exiting?", QMessageBox::Yes | QMessageBox::Cancel | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        save();
    } else if(reply != QMessageBox::No) {
        e->ignore();
    }
}

void GameWindow::save() {
    model.save();
}

//Key Event
//<k>The key player pressed/released
void GameWindow::keyPressEvent(QKeyEvent *k){
    if(k->key() == Qt::Key_Z) {
        PlaceableBlock* newBlock = model.placeBlock();
        if(newBlock != nullptr) {
            makeLabel(newBlock, placeableImg);
            newBlock->update();
        }
        ui->lblNumBlocks->setText(QString::number(model.getCurrentLevel()->getNumBlocks()));
    } else if(k->key() == Qt::Key_X){
    model.getCurrentLevel()->removeBlockX();
        ui->lblNumBlocks->setText(QString::number(model.getCurrentLevel()->getNumBlocks()));
    } else if (k->key() == Qt::Key_Escape) {
        menu->show();
    } else if (k->key() == Qt::Key_Space){
        if(!this->model.getCurrentLevel()->getPlayer()->hasBullet()){
            Bullet* b = model.fire();
            if(b != nullptr) {
                model.getCurrentLevel()->getPlayer()->setBullet(true);

                if(model.isCheating()) b->setInvincible(true);
                int dir = b->getDir();
                QPixmap map;
                if(model.isCheating() && dir == -1) map = cBulletImg;
                else if(model.isCheating() && dir == 1) map =  cBulletImgR;
                else if(dir == -1) map = bulletImg;
                else map = bulletImgR;

                QString cheat = model.isCheating() ? "c " : "n ";
                Network::instance().send("Bullet " + cheat + QString::number(b->getX()) + " " + QString::number(b->getY()) + " " + QString::number(b->getDir()));

                makeLabel(b, map);
            }
        }
    } else {
        model.playerInputP(k->key());
    }
}

void GameWindow::highScores() {
    display->update();
    display->show();
}

void GameWindow::endGame(bool done)
{
    if(done)
    {
        QMessageBox::information(this, "YOU LOST", "You lost all your lives. Try again.");
    }
    else
    {
        QMessageBox::information(this, "CONGRATULATIONS", "You won!");
    }

    bool ok = false;
    while(!ok)
    {
        QString userName = QInputDialog::getText(this, "High Score!", "Enter Your Name:", QLineEdit::Normal, "Banana", &ok);
        ScoreManager::instance().addHighScore(userName);
    }

    display->update();
    display->show();

    model.resetGame();
}

void GameWindow::focusOutEvent(QFocusEvent *) {
    model.getCurrentLevel()->getPlayer()->clearFlags();
}

void GameWindow::leaveEvent(QEvent *) {
    model.getCurrentLevel()->getPlayer()->clearFlags();
}

void GameWindow::keyReleaseEvent(QKeyEvent *k){
    if(k->key() == Qt::Key_R) {
        Network::instance().send("Reset");
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
        if(data.startsWith("Connect")) {
            QStringList list = data.split(" ");
            int id = list[1].toInt();
            if(id == 1) {
                Network::instance().send("Level " + QString::number(model.getLevelNumber()));
            }
            model.resetCurrentLevel();
            model.setUpdateGUI(true);
            otherPlayer = new RemotePlayer(model.getCurrentLevel(), 0, 0);
            model.getCurrentLevel()->setRemotePlayer(otherPlayer);
            QTimer* networkTimer = new QTimer(this);
            networkTimer->setInterval(1000 / 20);
            connect(networkTimer, SIGNAL(timeout()), this, SLOT(networkTimerHit()));
            networkTimer->start();
            updateGUI();
        } else if(data == "Finished") {
            model.levelFinished();
        } else if(data == "Reset") {
            model.resetCurrentLevel();
            updateGUI();
        } else if(data.startsWith("Collectible")) {
            QStringList list = data.split(" ");
            int x = list.at(1).toInt();
            int y = list.at(2).toInt();
            QList<Entity*> entities = model.getCurrentLevel()->getEntities();
            for(int i = 0; i < entities.size(); i++) {
                if(Collectible* c = dynamic_cast<Collectible*>(entities[i])) {
                    if(c->getX() == x && c->getY() == y) {
                        ScoreManager::instance().addToScore(c->getPoint());
                        Sound::instance().collect();
                        c->setRemoving(true);
                        break;
                    }
                }
            }
        } else if(data.startsWith("Remove")) {
            QStringList list = data.split(" ");
            int x = list.at(1).toInt();
            int y = list.at(2).toInt();
            Sound::instance().removeBlock();
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
        } else if(data.startsWith("Bullet")) {
            QStringList list = data.split(" ");
            bool cheat = list.at(1) == "c";
            int x = list.at(2).toInt();
            int y = list.at(3).toInt();
            int dir = list.at(4).toInt();
            Bullet* b = new Bullet(model.getCurrentLevel(), x, y);
            b->setDir(dir);
            QPixmap map;
            if(cheat) b->setInvincible(true);
            if(cheat && dir == -1) map = cBulletImg;
            else if(cheat && dir == 1) map = cBulletImgR;
            else if(dir == -1) map = bulletImg;
            else map = bulletImgR;

            makeLabel(b, map);
            model.getCurrentLevel()->getEntities() << b;
        } else if(data.startsWith("Level")) {
            QStringList list = data.split(" ");
            int lvl = list.at(1).toInt();
            model.setCurrentLevel(lvl - 1);
            model.getCurrentLevel()->setRemotePlayer(otherPlayer);
            model.getCurrentLevel()->load();
            model.setUpdateGUI(true);
        } else if(data.startsWith("Enemy")) {
            QStringList list = data.split(" ");
            int id = list.at(1).toInt();
            model.getCurrentLevel()->removeEnemyById(id);
        } else if(data.startsWith("Disconnect")) {
            QMessageBox::information(this, "Player disconnected", "The other player disconnected!");
            multiPlayer = false;
            otherPlayer->getBuddy()->deleteLater();
            delete otherPlayer;
            otherPlayer = nullptr;
        } else if(data.startsWith("LEAVE")) {
            QMessageBox::information(this, "Rejected", "Too many players already on server!");
            multiPlayer = false;
            delete otherPlayer;
            otherPlayer = nullptr;
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
    QMessageBox::information(this, "End of the World!", "<b style=\"color:red\">AHHHHHH THE SERVER DISCONNECTED!!! :(</b>");
    menu->show();
}

void GameWindow::socketError(QAbstractSocket::SocketError) {
    QMessageBox::information(this, "Couldn't connect!", "Couldn't connect to the server<br>Make sure the IP address is right.");
    menu->show();
}
