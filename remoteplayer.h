#ifndef REMOTEPLAYER_H
#define REMOTEPLAYER_H

#include "entity.h"

class RemotePlayer : public Entity
{
    int dir;
    int id;

    QPixmap pLeft;                //The image for facing left
    QPixmap pRight;               //The image for facing right

public:
    RemotePlayer(Level* initLevel, int initX, int initY);

    void update();
    void savePosition(QTextStream&) { }

    void dataReceived(QString data);

    void setDir(int newDir) { dir = newDir; }
    void setId(int newId) { id = newId; }

    int getDir() { return dir; }
    int getId() { return id; }
};

#endif // REMOTEPLAYER_H
