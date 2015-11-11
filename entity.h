//**********************************************************
// File: entity.h
// Desc: The main window's header file
//**********************************************************

#ifndef ENTITY_H
#define ENTITY_H

#include <QRect>
#include <QTextStream>
#include <QLabel>
#include <QDebug>

//Forward declaration of the level class, since level
//refers to entity and entity refers to level.
class Level;

class Entity
{
protected:
    Level* level;   //The level the entity is inside
    QRect rect;     //The entity's boudaries
    QLabel* buddy;  //The QLabel that the entity corresponds to

public:
    QString type;
    //Creates the entity with a starting x and y position
    //<initLevel> The level the entity is inside
    //<initX> The starting x position
    //<initY> The starting y position
    Entity(Level* initLevel, int initX, int initY) : level(initLevel), rect(initX, initY, SIZE, SIZE), buddy(nullptr) { }

    //Destructor for entity class
    virtual ~Entity() { }

    //Tests is the entity is touching any other entity
    //<otherEntity> The  entity to test if it's colliding
    bool isCollidingWith(Entity* otherEntity);

    //The pure virtual update method, used for updating position,
    //testing conditions, and anything else.
    virtual void update() = 0;

    //Saves the position of the entity to the save file
    virtual void savePosition(QTextStream &out) = 0;

    //Adds a certain amount to the x position of the entity
    //<amt> The amount to add to the x position
    void addX(int amt) { rect.moveTo(getX() + amt, getY()); }

    //Adds a certain amount to the y position of the entity
    //<amt> The amount to add to the y position
    void addY(int amt) { rect.moveTo(getX(), getY() + amt); }

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
    void setLevel(Level* newLevel) { level = newLevel; }

    //The default size of any entity
    static int SIZE;
};

#endif // ENTITY_H
