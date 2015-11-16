#include "scoredisplay.h"
#include "ui_scoredisplay.h"

ScoreDisplay::ScoreDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreDisplay)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle("High Scores");
    setFixedSize(geometry().width(), geometry().height());
}

ScoreDisplay::~ScoreDisplay()
{
    delete ui;
}

void ScoreDisplay::update()
{
    QString display = "<center><b style=\"color:green;\">";
    QStringList list = ScoreManager::instance().readScores();

    for(int i = 0; i < list.size(); i++) {
        display += list[i];
        if(i < list.size() - 1) display += "<hr style=\"size:3;\"/>";
    }

    display += "</b></center>";

    ui->txtScores->setText(display);
}

void ScoreDisplay::on_btnDone_clicked()
{
    hide();
}

void ScoreDisplay::on_btnClear_clicked()
{
    ScoreManager::instance().deleteHighScores();
    update();
}
