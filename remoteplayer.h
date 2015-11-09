#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include "entity.h"

class RemotePlayer : public Entity
{
    int dir;

    QPixmap pLeft;                //The image for facing left
    QPixmap pRight;               //The image for facing right

public:
    RemotePlayer(Level* initLevel, int initX, int initY);

    void update();
    void savePosition();

    void dataReceived(QString data);

    void setDir(int newDir) { dir = newDir; }

    int getDir() { return dir; }
};

#endif // REMOTEPLAYER_H
