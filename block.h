#ifndef BLOCK_H
#define BLOCK_H

#include "entity.h"

class Block : public Entity
{
private:
    //score that a block adds to total score (if it is placeable)
    int scorePlus;

    //whether or not a block is a stationary block
    bool prePlaced;
    //whether or not an inventory block has been placed
    bool placeable;
    bool placed;

public:
    Block();

    void update();
    void savePosition();

    //returns an amount to be added
    int toBeAdded();

    //getters
    int getScorePlus() { return scorePlus; }
    bool getPlaceable() { return placeable; }
    bool getPreplaced() { return prePlaced; }

    //setters
    void setPlaceable(bool newPlace) { placeable = newPlace; }
};

#endif // BLOCK_H
