//**********************************************************
// File: menu.cpp
// Desc: The game menu's implementation
//**********************************************************

#include "menu.h"
#include "ui_menu.h"
#include <QLabel>
#include <QDebug>
#include <QInputDialog>

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("Tandem Techies");
    setFixedSize(geometry().width(), geometry().height());

    QIcon icon(":/images/player.png");
    setWindowIcon(icon);

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
    QString server = "";
    bool ok;
    if(ui->btnMulti->isChecked()) {
        server = QInputDialog::getText(this, "Server IP", "Server IP Address:", QLineEdit::Normal, "10.20.2.137", &ok);
        if(!ok) return;
    }

    emit startGame(server);
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

void Menu::on_btnSingle_clicked()
{
    if(ui->btnSingle->isChecked()) {
        ui->btnMulti->setChecked(false);
    } else {
        ui->btnMulti->setChecked(true);
    }
}

void Menu::on_btnMulti_clicked()
{
    if(ui->btnMulti->isChecked()) {
        ui->btnSingle->setChecked(false);
    } else {
        ui->btnSingle->setChecked(true);
    }
}

void Menu::on_btnHighScores_clicked()
{
    emit highScores();
}
