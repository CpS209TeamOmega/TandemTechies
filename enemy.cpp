#include "level.h"
#include "enemy.h"

Enemy::Enemy(Level* initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    dir = 1;
    hSpeed = 4;
    eLeft.load(":/images/e_left.png");
    eRight.load(":/images/e_right.png");
}

void Enemy::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(dir == -1) {
        if(level->testCollision(getX() - 1, getY()) || !level->testCollision(getX(), getY() + getHeight() + 1)) {
            dir = 1;
        }
    } else if(dir == 1) {
        if(level->testCollision(getX() + Entity::SIZE + 1, getY()) || !level->testCollision(getX() + getWidth(), getY() + getHeight() + 1)) {
            dir = -1;
        }
    }

    addX(hSpeed * dir);

    if(isCollidingWith(level->getPlayer())) {
        level->getPlayer()->setDead(true);
    }

    if(dir == 1) {
        buddy->setPixmap(eRight);
    } else if(dir == -1) {
        buddy->setPixmap(eLeft);
    }
}

void Enemy::savePosition() {

}
