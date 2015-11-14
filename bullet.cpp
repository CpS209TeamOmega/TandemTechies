#include "bullet.h"
#include "level.h"
#include "sound.h"
#include "enemy.h"
#include "flyingenemy.h"



Bullet::Bullet(Level* initLevel, int initX, int initY, Player* ply)
       :Entity(initLevel, initX, initY)
{
    player = ply;
    dir = ply->getDir();
    hSpeed = 20;
    flying = true;
    ply->setBullet(true);
    Sound::instance().shoot();
}

void Bullet::update(){
    if(flying) {
        buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

        if(dir == -1) { //If going left
            if(level->testCollision(getX() - 1, getY()))  {
                this->setFlying(false);
                Sound::instance().colWall();
            }
        } else if(dir == 1) { //If going right
            if(level->testCollision(getX() + Entity::SIZE + 1, getY())) {
                this->setFlying(false);
                Sound::instance().colWall();
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
