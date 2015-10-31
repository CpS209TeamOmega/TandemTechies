//**********************************************************
// File: menu.cpp
// Desc: The game menu's implementation
//**********************************************************

#include "menu.h"
#include "ui_menu.h"
#include <QLabel>

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("Tandem Techies");

    QLabel* background = new QLabel(this);
    QPixmap backgroundImg(":/images/bg.png");
    background->setPixmap(backgroundImg);
    background->setGeometry(0, 0, geometry().width(), geometry().height());
    background->setScaledContents(true);
    background->lower();
    background->show();
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_btnStart_clicked()
{
    emit startGame();
    this->hide();
}

void Menu::on_btnLoad_clicked()
{
    emit loadGame();
}

void Menu::on_btnExit_clicked()
{
    emit exitGame();
    this->close();
}
