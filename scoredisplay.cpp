#include "scoredisplay.h"

ScoreDisplay *ScoreDisplay::instance_ = nullptr;

ScoreDisplay& ScoreDisplay::instance()
{
    if(instance_ == nullptr)
    {
        instance_ = new ScoreDisplay();
    }
    return *instance_;
}
