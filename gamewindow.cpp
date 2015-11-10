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
#include "sound.h"
#include <QLabel>
#include <QDebug>
#include <QObject>
#include <QObjectList>
#include <QMessageBox>
#include <QKeyEvent>
#include <QFile>
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

void GameWindow::load() {
    QFile loadFile("save.dat");
    if(!loadFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not load save file.";
        return;
    }

    qDebug() << "Loading save file.";
    QTextStream in(&loadFile);

    while(!in.atEnd()) {
        QString line = in.readLine();

        if(!line.isEmpty()) {
            if(line.startsWith("Chicken")) { //Level number
                QStringList list = line.split(" ");
                model.setCurrentLevel(list[1].toInt());
                model.getCurrentLevel()->removeAllEntities();
            } else if(line.startsWith("Banana")) { //Player position
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                int dir = list[3].toInt();
                Player* p = model.getCurrentLevel()->getPlayer();
                p->setX(x);
                p->setY(y);
                p->setWidth(Entity::SIZE);
                p->setHeight(Entity::SIZE);
                p->setDir(dir);
            } else if(line.startsWith("Goodguy")) { //Enemy position
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                int dir = list[3].toInt();
                Enemy* e = new Enemy(model.getCurrentLevel(), x, y);
                e->setDir(dir);
                model.getCurrentLevel()->getEntities() << e;
            } else if(line.startsWith("Enchilada")) { //Collectibles
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                model.getCurrentLevel()->getEntities() << new Collectible(model.getCurrentLevel(), x, y);
            } else if(line.startsWith("Broccoli")) { //Placeable Blocks
                QStringList list = line.split(" ");
                int x = list[1].toInt();
                int y = list[2].toInt();
                model.getCurrentLevel()->getBlocks()[y / Entity::SIZE][x / Entity::SIZE] = new PlaceableBlock(model.getCurrentLevel(), x, y);
            }
        }
    }
    model.setUpdateGUI(true);
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
    qDebug() << "Saving Game File";

    QFile saveFile("save.dat");
    if(!saveFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error saving game data";
        return;
    }

    QTextStream out(&saveFile);

    Level* current = model.getCurrentLevel();

    out << "Chicken " << model.getLevelNumber() - 1 << "\n";

    Player* p = current->getPlayer();
    out << "Banana " << p->getX() << " " << p->getY() << " " << p->getDir() << "\n";

    QList<Entity*> ents = current->getEntities();
    for(int i = 0; i < ents.size(); i++) {
        Enemy* e = dynamic_cast<Enemy*>(ents[i]);
        if(e) out << "Goodguy " << e->getX() << " " << e->getY() << " " << e->getDir() << "\n";

        Collectible* c = dynamic_cast<Collectible*>(ents[i]);
        if(c) out << "Enchilada " << c->getX() << " " << c->getY() << "\n";
    }

    QList<QList<Block*>> blocks = model.getCurrentLevel()->getBlocks();
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            PlaceableBlock* b = dynamic_cast<PlaceableBlock*>(blocks[y][x]);
            if(b) out << "Broccoli " << b->getX() << " " << b->getY() << "\n";
        }
    }
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
        } else if(data.startsWith("Level")) {
            QStringList list = data.split(" ");
            int lvl = list.at(1).toInt();
            model.setCurrentLevel(lvl);
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
    qDebug() << "COULDN'T CONNECT";
}
