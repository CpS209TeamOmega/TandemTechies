#include "scoredisplay.h"
#include "ui_scoredisplay.h"

ScoreDisplay::ScoreDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreDisplay)
{
    ui->setupUi(this);
}

ScoreDisplay::~ScoreDisplay()
{
    delete ui;
}

