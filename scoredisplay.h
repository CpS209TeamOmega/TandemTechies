#ifndef SCOREDISPLAY_H
#define SCOREDISPLAY_H

#include <QFile>

#include "scoremanager.h"

class ScoreDisplay
{
private:
    ScoreDisplay() { }

    static ScoreDisplay *instance_;

public:
    static ScoreDisplay& instance();
};

#endif // SCOREDISPLAY_H
