#include "scoredisplay.h"
#include "ui_scoredisplay.h"

ScoreDisplay::ScoreDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreDisplay)
{
    ui->setupUi(this);

    scoreText = new QLabel(this);
    scoreText->setGeometry(0, 0, geometry().width(), geometry().height());
    scoreText->raise();

    connect(menu, SIGNAL(highScores()), this, SLOT(displayScores()));
    connect(game, SIGNAL(scores()), this, SLOT(displayScores()));
}

ScoreDisplay::~ScoreDisplay()
{
    delete ui;
}

void ScoreDisplay::displayScores()
{
    scoreText->setText(ScoreManager::instance().readScores());
    scoreText->show();
}
