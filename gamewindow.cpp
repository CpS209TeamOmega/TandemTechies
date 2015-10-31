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
#include <QtGlobal>
#include <QIcon>

//The default width of the game
int GameWindow::WIDTH = 1024;

//The default height
int GameWindow::HEIGHT = 768;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    QIcon windowIcon(":/images/player.png");
    setWindowIcon(windowIcon);
    setFixedSize(WIDTH, HEIGHT);
    setWindowTitle("Tandem Techies");
    fps = 60;

    menu = new Menu();
    menu->show();

    //Connect slots with signal from Menu
    QObject::connect(menu, SIGNAL(startGame()), this, SLOT(start()));
    QObject::connect(menu, SIGNAL(loadGame()), this, SLOT(load()));
    QObject::connect(menu, SIGNAL(exitGame()), this, SLOT(exit()));

    blockImg.load(":/images/block.png");
    playerImg.load(":/images/player.png");
    exitImg.load(":/images/exit.png");
    backgroundImg.load(":/images/bg.png");

    if(!model.loadLevels()) {
        qDebug() << "Couldn't load the levels!";
        exit();
	}
	else {
		unitTests();
        updateGUI();

		QTimer *timer = new QTimer(this);
		timer->setInterval(1000 / fps);
		connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
		timer->start();
	}
}

void GameWindow::unitTests() {
	Level* level = model.getCurrentLevel();

	//Make sure the level's name is as it shows in levels.dat
	Q_ASSERT(level->getName() == "Beginning your journey");

	//Make sure the number of placeable blocks reflects levels.dat
	Q_ASSERT(level->getNumBlocks() == 3);

	//Make sure the level loaded correctly - level height == 7
	Q_ASSERT(level->getBlocks().size() == 7);

	//Make sure the level loaded correctly - level width == 12
	Q_ASSERT(level->getBlocks()[0].size() == 12);

	//Make sure the player's x position in the level is 64
	Q_ASSERT(level->getPlayer()->getX() == 64);

	//Make sure the player's y position in the level is 320
	Q_ASSERT(level->getPlayer()->getY() == 320);

	//All unit tests passed! Now on to play this amazing game!
}

void GameWindow::makeLabel(Entity* e, QPixmap image) {
    QLabel* lbl = new QLabel(this);			//Create the label
    lbl->setGeometry(e->getRect());			//Sets the geometry to reflect the entity
    lbl->setPixmap(image);					//Sets the picture of the label
    lbl->setScaledContents(true);			//Makes the picture scale to the label's size
    e->setBuddy(lbl);						//Sets the Entity's corresponding label
	lbl->show();
}

void GameWindow::updateGUI() {
	//Clear all of the current labels from the window
    QObjectList objects = children();
    for(QObject* object : objects) {
        QLabel* lbl = dynamic_cast<QLabel*>(object);
        if(lbl != nullptr) {
            lbl->deleteLater();
        }
    }

	//Load up the background image
	QLabel* lbl = new QLabel(this);
	lbl->setGeometry(0, 0, WIDTH, HEIGHT);
	lbl->setPixmap(backgroundImg);
	lbl->setScaledContents(true);
	lbl->show();

	//Get the current level
    Level* lvl = model.getCurrentLevel();

    auto entities = lvl->getEntities();
    for(int i = 0; i < entities.size(); i++) {
        makeLabel(entities[i], backgroundImg);
    }

	//Create the labels for the blocks in the level
    auto blocks = lvl->getBlocks();
    for(int y = 0; y < blocks.size(); y++) {
        for(int x = 0; x < blocks[y].size(); x++) {
            if(blocks[y][x] != nullptr) {
                  Block* b = blocks[y][x];
                  makeLabel(b, blockImg);
            }
        }
    }

	//Create the player's label
    Player* p = lvl->getPlayer();
    makeLabel(p, playerImg);

	//Create the exit's label
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
    if (k->key() == Qt::Key_Escape) {
        menu->show();
    }

    model.playerInputP(k->key());
}

void GameWindow::keyReleaseEvent(QKeyEvent *k){
    model.playerInputR(k->key());
}
