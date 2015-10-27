#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QLabel>
#include <QDebug>

#include <QKeyEvent>

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    setFixedSize(1024, 768);

    if(!model.loadLevels()) {
        qDebug() << "Couldn't load the levels!";
        deleteLater();
    } else {
         QPixmap blockPic(":/images/block.png");
         auto blocks = model.getCurrentLevel()->getBlocks();
         for(int y = 0; y < blocks.size(); y++) {
             for(int x = 0; x < blocks[y].size(); x++) {
                 if(blocks[y][x] != nullptr) {
                       Block* b = blocks[y][x];
                       QLabel* lbl = new QLabel(this);
                       lbl->setGeometry(b->getX(), b->getY(), b->getWidth(), b->getHeight());
                       lbl->setPixmap(blockPic);
                       lbl->setScaledContents(true);
                       lbl->show();
                 }
             }
         }

         Player p = model.getCurrentLevel()->getPlayer();
         QLabel* plbl = new QLabel(this);
         plbl->setGeometry(p.getX(), p.getY(), p.getWidth(), p.getHeight());
         QPixmap playerPic(":/images/player.png");
         plbl->setPixmap(playerPic);
         plbl->setScaledContents(true);
         plbl->show();
    }

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
