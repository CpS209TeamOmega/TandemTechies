#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QMediaPlayer>
#include <QSoundEffect>

class SoundManager
{
    QMediaPlayer* player;

    QUrl backMusic;

public:
    ~SoundManager();

    void playBackgroundMusic();
    void stopBackgroundMusic();
    void init();

private:
    static SoundManager* instance_;

public:
    static SoundManager& instance();
};

#endif // SOUNDMANAGER_H
