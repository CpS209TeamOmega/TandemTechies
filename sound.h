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
    QSoundEffect killedEnemy_;
    QSoundEffect hitGround_;
    QSoundEffect cheatOn_;
    QSoundEffect cheatOff_;

public:
    void endLevel();
    void gameOver();
    void collect();
    void placeBlock();
    void removeBlock();
    void killedEnemy();
    void hitGround();
    void cheatOn();
    void cheatOff();

    static Sound& instance();

private:
    static Sound* instance_;
};

#endif // SOUND_H
