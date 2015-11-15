#ifndef SOUND_H
#define SOUND_H

#include <QThread>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class Sound
{
    Sound();
    ~Sound();

    QMediaPlayer player;
    QMediaPlaylist* playlist;

    QSoundEffect endLevel_;
    QSoundEffect gameOver_;
    QSoundEffect collect_;
    QSoundEffect placeBlock_;
    QSoundEffect removeBlock_;
    QSoundEffect killedEnemy_;
    QSoundEffect hitGround_;
    QSoundEffect cheatOn_;
    QSoundEffect cheatOff_;
    QSoundEffect shoot_;
    QSoundEffect dead_;
    QSoundEffect colWall_;

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
    void backGround();
    void shoot();
    void dead();
    void colWall();

    bool getBack();

    static Sound& instance();

private:
    static Sound* instance_;
};

#endif // SOUND_H
