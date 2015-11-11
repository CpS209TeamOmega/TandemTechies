#include "level.h"
#include "collectible.h"
#include "network.h"
#include "sound.h"

void Collectible::update() {
    if(buddy) buddy->move(getX() - level->getXOffs(), getY() - level->getYOffs());

    if(isCollidingWith(level->getPlayer())) {
        deleteCollectible();
    }
}

void Collectible::deleteCollectible()
{
    Network::instance().send("Collectible " + QString::number(getX()) + " " + QString::number(getY()));
    Sound::instance().collect();
    ScoreManager::instance().addToScore(pointPlus);
    buddy->deleteLater();
    level->removeEntity(this);
}

void Collectible::savePosition(QTextStream &out) {
    out << "Collect " << getX() << " " << getY() << "\n";
}
