#include "level.h"
#include "flyingenemy.h"
#include "sound.h"

FlyingEnemy::FlyingEnemy(Level* initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY) {
    type = "FlyingEnemy";
    dir = 1;
    hSpeed = 4;
    dead = false;
    curHeight = Entity::SIZE;
    flyingEnemy.load(":/images/flyingEnemy.png");
    flyingEnemy2.load(":/images/flyingEnemy2.png");
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

                dead = true;
                p->setVib(true);
            } else {
                p->setDead(true);
            }
        }

        if(dir == 1) {
            buddy->setPixmap(flyingEnemy2);
        } else if(dir == -1) {
            buddy->setPixmap(flyingEnemy);
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
