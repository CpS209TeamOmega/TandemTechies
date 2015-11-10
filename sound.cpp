#include "sound.h"

Sound* Sound::instance_ = nullptr;

Sound& Sound::instance() {
    if(instance_ == nullptr) {
        instance_ = new Sound();
    }
    return *instance_;
}

Sound::Sound()
{
    endLevel_.setSource(QUrl("qrc:/soundeffects/newLevel.wav"));
    gameOver_.setSource(QUrl("qrc:/soundeffects/gameOver.wav"));
    collect_.setSource(QUrl("qrc:/soundeffects/collect.wav"));
    placeBlock_.setSource(QUrl("qrc:/soundeffects/place_block.wav"));
    removeBlock_.setSource(QUrl("qrc:/soundeffects/remove_block.wav"));
}

void Sound::placeBlock() {
    placeBlock_.play();
}

void Sound::removeBlock() {
    removeBlock_.play();
}

void Sound::endLevel() {
    endLevel_.play();
}

void Sound::gameOver() {
    gameOver_.play();
}

void Sound::collect() {
    collect_.play();
}
