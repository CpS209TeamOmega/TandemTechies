//**********************************************************
// File: menu.cpp
// Desc: The game menu's implementation
//**********************************************************

#include "menu.h"
#include "ui_menu.h"
#include <QLabel>
#include <QDebug>

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{

    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("Tandem Techies");
    setFixedSize(geometry().width(), geometry().height());

    QLabel* cover = new QLabel(this);
    cover->setStyleSheet("background-color:rgba(0,0,0,.8);");
    cover->setGeometry(0, 0, geometry().width(), geometry().height());
    cover->lower();
    cover->show();

    QLabel* background = new QLabel(this);
    QPixmap backgroundImg(":/images/bg.png");
    background->setPixmap(backgroundImg);
    background->setGeometry(0, 0, geometry().width(), geometry().height());
    background->setScaledContents(true);
    background->lower();
    background->show();

    //Make the logo's background transparent
    ui->lblLogo->setAttribute(Qt::WA_TranslucentBackground);

    //Make the menu border invisible
    setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    setWindowFlags(Qt::CustomizeWindowHint);
    setWindowFlags(Qt::FramelessWindowHint);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_btnStart_clicked()
{
    ui->btnStart->setText("Resume");
    emit startGame();
    hide();
}

void Menu::on_btnLoad_clicked()
{
    emit loadGame();
    hide();
}

void Menu::on_btnExit_clicked()
{
    emit exitGame();
    close();
}

void Menu::closeEvent(QCloseEvent*) {
    emit exitGame();
}
