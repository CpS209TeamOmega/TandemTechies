#include "level.h"
#include "collectible.h"

void Collectible::update() {
    buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(isCollidingWith(level->getPlayer())) {
        deleteCollectible();
    }
}

void Collectible::deleteCollectible()
{
    buddy->deleteLater();
    level->removeEntity(this);
}

void Collectible::savePosition() {

}
