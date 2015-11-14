#include "bullet.h"
#include "level.h"
#include "sound.h"
#include "enemy.h"
#include "flyingenemy.h"

#include <QDebug>


Bullet::Bullet(Level* initLevel, int initX, int initY, Player* ply): Entity(initLevel, initX, initY), player(ply)
{
    dir = ply->getDir();
    hSpeed = 10;
    flying = true;
    Sound::instance().cheatOn();
}

void Bullet::update(){
    if(flying) {
        qDebug() << getX() << " " << getY();
        buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

        if(dir == -1) { //If going left
            if(level->testCollision(getX() - 1, getY()))  {
                this->setFlying(false);
            }
        } else if(dir == 1) { //If going right
            if(level->testCollision(getX() + Entity::SIZE + 1, getY())) {
                this->setFlying(false);
            }
        }

        addX(hSpeed * dir);


        QList<Entity*> entities = level->getEntities();
        for (int i = 0; i < entities.length(); i++){
            Enemy* enemy = dynamic_cast<Enemy*> (entities[i]);
            if ((this->isCollidingWith(entities[i]))&&(enemy != nullptr)){
                enemy->setDead(true);
                this->setFlying(false);
            }
            FlyingEnemy* flyingenemy = dynamic_cast<FlyingEnemy*> (entities[i]);
            if ((this->isCollidingWith(entities[i]))&&(flyingenemy != nullptr)){
                flyingenemy->setDead(true);
                this->setFlying(false);
            }
        }

    } else {
        buddy->deleteLater();
        level->removeEntity(this);
    }
}

void Bullet::savePosition(QTextStream &out){out << "";}
