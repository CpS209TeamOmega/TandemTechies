#ifndef ENTITY_H
#define ENTITY_H

#include <QRect>
#include <QLabel>
#include <QDebug>

class Level;

class Entity
{
protected:
    Level* level;
    QRect rect;
    QLabel* buddy;

public:
    Entity(Level* initLevel) : level(initLevel), rect(0, 0, SIZE, SIZE), buddy(nullptr) { }
    Entity(Level* initLevel, int initX, int initY) : level(initLevel), rect(initX, initY, SIZE, SIZE), buddy(nullptr) { }

    bool isCollidingWith(Entity* otherEntity);

    virtual void update() = 0;

    virtual void savePosition() = 0;

    void addX(int amt) { rect.setX(rect.x() + amt); }
    void addY(int amt) { rect.setY(rect.y() + amt); }

    //Getters
    int getX() { return rect.x(); }
    int getY() { return rect.y(); }
    int getWidth() { return rect.width(); }
    int getHeight() { return rect.height(); }
    QLabel* getBuddy() { return buddy; }
    QRect getRect() { return rect; }

    //Setters
    void setX(int newX) { rect.setX(newX); }
    void setY(int newY) { rect.setY(newY); }
    void setWidth(int newWidth) { rect.setWidth(newWidth); }
    void setHeight(int newHeight) { rect.setHeight(newHeight); }
    void setBuddy(QLabel* newBuddy) { buddy = newBuddy; }

    static int SIZE;
};

#endif // ENTITY_H
