#include "level.h"
#include "collectible.h"
#include "network.h"

void Collectible::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(isCollidingWith(level->getPlayer())) {
        deleteCollectible();
    }
}

void Collectible::deleteCollectible()
{
    Network::instance().send("Collectible " + QString::number(getX()) + " " + QString::number(getY()));

    ScoreManager::instance().addToScore(pointPlus);
    buddy->deleteLater();
    level->removeEntity(this);
}

void Collectible::savePosition() {

}
