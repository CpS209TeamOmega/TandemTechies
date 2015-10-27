#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_btnStart_clicked()
{
    emit startGame();
    this->close();
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
