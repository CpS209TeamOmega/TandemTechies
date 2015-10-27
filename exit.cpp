#include "level.h"
#include "exit.h"

void Exit::update() {
    if(isCollidingWith(level->getPlayer())) {
        qDebug() << "Level finished!";
    }

    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());
}

void Exit::savePosition() {

}
