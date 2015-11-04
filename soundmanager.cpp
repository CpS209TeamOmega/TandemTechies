#include "soundmanager.h"

SoundManager* SoundManager::instance_ = nullptr;

SoundManager& SoundManager::instance() {
    if(instance_ == nullptr) {
        instance_ = new SoundManager();
    }
    return *instance_;
}

SoundManager::~SoundManager() {
    player->stop();
    delete player;
}

void SoundManager::init() {
    backMusic = QUrl::fromLocalFile("/Documents/Music/K-391/Solstice.mp3");
    player = new QMediaPlayer();
}

void SoundManager::playBackgroundMusic() {
    player->setMedia(backMusic);
    player->setVolume(100);
    player->play();
}

void SoundManager::stopBackgroundMusic() {
    player->stop();
}
