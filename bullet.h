#ifndef BULLET_H
#define BULLET_H

#include "entity.h"
#include "player.h"

class Bullet : public Entity
{
private:
    bool flying;
    int hSpeed;					  //The bullet's velocity
    int dir;					  //The direction the bullet is currently facing
    int curWidth;
    bool invincible;
public:
    Bullet(Level* initLevel, int initX, int initY);

    ~Bullet() { }

    bool isFlying(){ return flying; }
    int getDir(){return dir;}
    bool isInvincible() { return invincible; }

    void setFlying(bool f){ flying = f; }
    void setInvincible(bool i){invincible = i;}
    void setDir(int newDir) { dir = newDir; }

    void update();

    void savePosition(QTextStream &out);
};

#endif // BULLET_H
