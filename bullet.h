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
    int curWidth;
    bool invincible;
public:
    Bullet(Level* initLevel, int initX, int initY, Player* ply);

    //~Bullet();

    bool isFlying(){ return flying; }
    int getDir(){return dir;}

    void setFlying(bool f){ flying = f; }
    void setInvincible(bool i){invincible = i;}

    void update();

    void savePosition(QTextStream &out);
};

#endif // BULLET_H
