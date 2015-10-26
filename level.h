#ifndef LEVEL_H
#define LEVEL_H

#include "player.h"
#include "block.h"
#include "exit.h"
#include <QString>
#include <QList>

class Level
{
    Player* player;
    Exit* exit;
    QList<QList<Block*>> blocks;
    int numBlocks;
    QString name;

public:
    Level(QList<QString> data);
    ~Level();

    void update();
    void load(QList<QString> data);

    void setName(QString newName) { name = newName; }
    void setNumBlocks(int newNum) { numBlocks = newNum; }
};

#endif // LEVEL_H
