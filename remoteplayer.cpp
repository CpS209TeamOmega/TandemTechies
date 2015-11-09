#include "level.h"
#include "remoteplayer.h"

RemotePlayer::RemotePlayer(Level *initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    dir = 1;

    pLeft.load(":/images/p2_left.png");
    pRight.load(":/images/p2_right.png");
}

void RemotePlayer::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(dir == 1) {
        buddy->setPixmap(pRight);
    } else if(dir == -1) {
        buddy->setPixmap(pLeft);
    }
}

void RemotePlayer::dataReceived(QString data) {
    QStringList split = data.split(" ");
    setX(split.at(0).toInt());
    setY(split.at(1).toInt());
    setDir(split.at(2).toInt());
}

void RemotePlayer::savePosition() {

}
