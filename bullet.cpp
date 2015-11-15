#include "bullet.h"
#include "level.h"
#include "sound.h"
#include "enemy.h"



Bullet::Bullet(Level* initLevel, int initX, int initY)
       :Entity(initLevel, initX, initY)
{
    dir = 1;
    hSpeed = 12;
    flying = true;
    Sound::instance().shoot();
    curWidth = Entity::SIZE;
    invincible = false;
}

void Bullet::update(){
    if(flying) {
        buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

        if(dir == -1) { //If going left
            if(level->testCollision(getX() - 1, getY()))  {
                Sound::instance().colWall();
                this->setFlying(false);                
            }
        } else if(dir == 1) { //If going right
            if(level->testCollision(getX() + Entity::SIZE + 1, getY())) {
                Sound::instance().colWall();
                this->setFlying(false);
            }
        }

        addX(hSpeed * dir);


        QList<Entity*> entities = level->getEntities();
        for (int i = 0; i < entities.length(); i++){
            Enemy* enemy = dynamic_cast<Enemy*> (entities[i]);
            if ((this->isCollidingWith(entities[i]))&&(enemy != nullptr)){
                enemy->setDead(true);
                if(!invincible)this->setFlying(false);
            }
            FlyingEnemy* flyingenemy = dynamic_cast<FlyingEnemy*> (entities[i]);
            if ((this->isCollidingWith(entities[i]))&&(flyingenemy != nullptr)){
                flyingenemy->setDead(true);
                if(!invincible)this->setFlying(false);
            }
        }

    } else {
        curWidth -= 16;
        if(curWidth > 0) {
            if(dir == -1){
                buddy->setGeometry(getX() - level->getXOffs(), getY() - level->getYOffs(), curWidth, getHeight());
            } else if(dir == 1){
                buddy->setGeometry(getX() + (getWidth() - curWidth)  - level->getXOffs(), getY() - level->getYOffs(), curWidth, getHeight());
            }
        } else {
            buddy->deleteLater();
            level->removeEntity(this);
        }
    }
}

void Bullet::savePosition(QTextStream &out){
    QString cheat = invincible ? "c " : "n ";
    out << "Bullet " << cheat << QString::number(getX()) << " " << QString::number(getY()) << " " << QString::number(dir) << "\n";
}
