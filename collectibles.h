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
    bool getCollect();
    int getX() { return rect.x(); }
    int getY() { return rect.y(); }
    int getScorePlus() { return scorePlus; }

    //setters
    void setCollect(bool newBool) { collected = newbool; }
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};

#endif // COLLECTIBLES_H
