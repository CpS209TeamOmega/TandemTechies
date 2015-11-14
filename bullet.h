#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include "player.h"

class Bullet : public Entity
{
private:
    Player* player;
    bool flying;
    int hSpeed;					  //The bullet's velocity
    int dir;					  //The direction the bullet is currently facing
public:
    Bullet(Level* initLevel, int initX, int initY, Player* ply);

    bool isFlying(){ return flying; }
    int getDir(){return dir;}

    void setFlying(bool f){ flying = f; }

    void update();

    void savePosition(QTextStream &out);
};

#endif // BULLET_H
