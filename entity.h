#ifndef ENTITY_H
#define ENTITY_H

#include <QRect>

class Level;

class Entity
{
    static int SIZE;

protected:
    Level* level;
    QRect rect;

public:
    Entity(Level* initLevel) : level(initLevel), rect(0, 0, SIZE, SIZE) { }
    Entity(Level* initLevel, int initX, int initY) : level(initLevel), rect(initX, initY, SIZE, SIZE) { }

    bool isCollidingWith(Entity& otherEntity);

    virtual void update() = 0;

    virtual void savePosition() = 0;

    //Getters
    int getX() { return rect.x(); }
    int getY() { return rect.y(); }
    int getWidth() { return rect.width(); }
    int getHeight() { return rect.height(); }
    QRect getRect() { return rect; }

    //Setters
    void setX(int newX) { rect.setX(newX); }
    void setY(int newY) { rect.setY(newY); }
    void setWidth(int newWidth) { rect.setWidth(newWidth); }
    void setHeight(int newHeight) { rect.setHeight(newHeight); }
};

#endif // ENTITY_H
