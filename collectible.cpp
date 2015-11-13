#include "level.h"
#include "collectible.h"
#include "network.h"
#include "sound.h"
#include <QPainter>

Collectible::Collectible(Level *initLevel, int initX, int initY)
    : Entity(initLevel, initX, initY), pointPlus(50),
      removing(false), curSize(Entity::SIZE), maxSize(128) { }

void Collectible::update() {
    if(!removing) {
        if(buddy) buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

        if(isCollidingWith(level->getPlayer())) {
            removing = true;
            Network::instance().send("Collectible " + QString::number(getX()) + " " + QString::number(getY()));
            Sound::instance().collect();
            ScoreManager::instance().addToScore(pointPlus);
        }
    } else {
        if(curSize < maxSize) {
            curSize += 8;
            buddy->setGeometry(getX() + (Entity::SIZE / 2 - curSize / 2) - level->getXOffs(), getY() + (Entity::SIZE / 2 - curSize / 2) - level->getYOffs(), curSize, curSize);
        } else {
            deleteCollectible();
        }
    }
}

void Collectible::deleteCollectible()
{
    buddy->deleteLater();
    level->removeEntity(this);
}

void Collectible::savePosition(QTextStream &out) {
    out << "Collect " << getX() << " " << getY() << "\n";
}
