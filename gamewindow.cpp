#include "gamewindow.h"
#include "ui_gamewindow.h"

#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

}

GameWindow::~GameWindow()
{
    delete ui;
}

/*GameWindow::keyPressEvent(QKeyEvent *k){
    switch (k->key()){
    case Qt::Key_Up:

        break;
    case Qt::Key_Down:

        break;
    case Qt::Key_Left:

        break;
    case Qt::Key_Right:

        break;
    default:

        break;
    }
}
*/
