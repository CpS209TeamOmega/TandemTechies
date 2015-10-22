#ifndef ENTITY_H
#define ENTITY_H

#include <QRect>

class Entity
{
    QRect rect;

public:
    Entity();

    //save the status of an entity
    virtual void keepMeHere();

    bool isCollidingWith(Entity& otherEntity);

    void update() = 0;

    //Getters
    int getX() { return rect.x(); }
    int getY() { return rect.y(); }
    int getWidth() { return rect.width(); }
    int getHeight() { return rect.height(); }
    QRect getRect() { return rect; }

    //Setters
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setWidth(int newWidth) { width = newWidth; }
    void setHeight(int newHeight) { height = newHeight; }
};

#endif // ENTITY_H
