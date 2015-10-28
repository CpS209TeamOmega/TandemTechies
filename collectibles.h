#ifndef COLLECTIBLES_H
#define COLLECTIBLES_H

#include "entity.h"

class Collectibles : public Entity
{
private:
    //whether or not a collectible has been collected
    bool collected;

    //score that this entitiy adds to total score
    int scorePlus;

public:
    Collectibles();

    void update();
    void savePosition();

    //delete the collectible
    void deleteCollectible();

    //getters
    bool getCollect() { return collected; }
    int getX() { return getRect().x(); }
    int getY() { return getRect().y(); }
    int getScorePlus() { return scorePlus; }

    //setters
    void setCollect(bool newBool) { collected = newBool; }
//    void setX(int newX) { getX() = newX; }
//    void setY(int newY) { getY() = newY; }
};

#endif // COLLECTIBLES_H
