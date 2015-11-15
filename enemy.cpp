#include "level.h"

#include "network.h"
#include "enemy.h"
#include "sound.h"

Enemy::Enemy(Level* initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    type = "Enemy";
    dir = 1;
    hSpeed = 4;
    dead = false;
    curHeight = Entity::SIZE;
    eLeft.load(":/images/e_left.png");
    eRight.load(":/images/e_right.png");
}

void Enemy::update() {
    if(!dead) {
        buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

        if(dir == -1) { //If going left
            if(level->testCollision(getX() - 1, getY()) || !level->testCollision(getX(), getY() + getHeight() + 1)) {
                dir = 1;
            }
        } else if(dir == 1) { //If going right
            if(level->testCollision(getX() + Entity::SIZE + 1, getY()) || !level->testCollision(getX() + getWidth(), getY() + getHeight() + 1)) {
                dir = -1;
            }
        }

        addX(hSpeed * dir);

        Player* p = level->getPlayer();
        if(isCollidingWith(p)) {
            QRect test(getX(), getY(), getWidth(), 32);
            if(p->isInvincible() || test.contains(p->getX(), p->getY() + p->getHeight()) || test.contains(p->getX() + p->getWidth(), p->getY() + p->getHeight())) {
                Network::instance().send("Enemy " + QString::number(id));
                dead = true;
                p->setVib(true);
            } else {
                p->setDead(true);
            }
        }

        if(dir == 1) {
            buddy->setPixmap(eRight);
        } else if(dir == -1) {
            buddy->setPixmap(eLeft);
        }
    } else {        
        curHeight -= 8;
        if(curHeight > 0) {
            buddy->setGeometry(getX() - level->getXOffs(), getY() + (getHeight() - curHeight) - level->getYOffs(), getWidth(), curHeight);
        } else {
            Sound::instance().killedEnemy();
            buddy->deleteLater();
            level->removeEntity(this);
        }
    }
}

void Enemy::savePosition(QTextStream &out) {
    out << "Enemy " << getX() << " " << getY() << " " << dir << "\n";
}

FlyingEnemy::FlyingEnemy(Level* initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    type = "FlyingEnemy";
    dir = 1;
    hSpeed = 4;
    dead = false;
    curHeight = Entity::SIZE;
    feLeft.load(":/images/fly_e_left.png");
    feRight.load(":/images/fly_e_right.png");
}

void FlyingEnemy::update() {
    if(!dead) {
        buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

        if(dir == -1) { //If going left
            if(level->testCollision(getX() - 1, getY())) {
                dir = 1;
            }
        } else if(dir == 1) { //If going right
            if(level->testCollision(getX() + Entity::SIZE + 1, getY())) {
                dir = -1;
            }
        }

        addX(hSpeed * dir);

        Player* p = level->getPlayer();
        if(isCollidingWith(p)) {
            QRect test(getX(), getY(), getWidth(), 32);
            if(p->isInvincible() || test.contains(p->getX(), p->getY() + p->getHeight()) || test.contains(p->getX() + p->getWidth(), p->getY() + p->getHeight())) {
                Network::instance().send("Enemy " + QString::number(id));
                dead = true;
                p->setVib(true);
            } else {
                p->setDead(true);
            }
        }

        if(dir == 1) {
            buddy->setPixmap(feRight);
        } else if(dir == -1) {
            buddy->setPixmap(feLeft);
        }
    } else {
        if(curHeight > 8) {
            curHeight -= 8;
            buddy->setGeometry(getX() + (Entity::SIZE / 2 - curHeight / 2) - level->getXOffs(), getY() + (Entity::SIZE / 2 - curHeight / 2) - level->getYOffs(), curHeight, curHeight);
        } else {
            Sound::instance().killedEnemy();
            buddy->deleteLater();
            level->removeEntity(this);
        }
    }
}

void FlyingEnemy::savePosition(QTextStream &out) {
    out << "FlyingEnemy " << getX() << " " << getY() << " " << dir << "\n";
}
