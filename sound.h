#ifndef SOUND_H
#define SOUND_H

#include <QThread>
#include <QSoundEffect>

class Sound
{
    Sound();

    QSoundEffect endLevel_;
    QSoundEffect gameOver_;
    QSoundEffect collect_;
    QSoundEffect placeBlock_;
    QSoundEffect removeBlock_;

public:
    void endLevel();
    void gameOver();
    void collect();
    void placeBlock();
    void removeBlock();

    static Sound& instance();

private:
    static Sound* instance_;
};

#endif // SOUND_H
