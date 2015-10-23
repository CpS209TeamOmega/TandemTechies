#ifndef ENTITY_H
#define ENTITY_H

#include <QRect>

class Entity
{
    QRect rect;

public:
    Entity();

    bool isCollidingWith(Entity& otherEntity);

    virtual void update() = 0;

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
