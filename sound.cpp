#include "sound.h"
#include <QFile>
#include <QDir>

Sound* Sound::instance_ = nullptr;

Sound& Sound::instance() {
    if(instance_ == nullptr) {
        instance_ = new Sound();
    }
    return *instance_;
}

Sound::Sound()
{
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(QDir().absoluteFilePath(QString("back.wav"))));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    playlist->setCurrentIndex(1);
    player.setPlaylist(playlist);
    player.setVolume(50);
    player.play();

    endLevel_.setSource(QUrl("qrc:/soundeffects/newLevel.wav"));
    gameOver_.setSource(QUrl("qrc:/soundeffects/gameOver.wav"));
    collect_.setSource(QUrl("qrc:/soundeffects/collect.wav"));
    placeBlock_.setSource(QUrl("qrc:/soundeffects/place_block.wav"));
    removeBlock_.setSource(QUrl("qrc:/soundeffects/remove_block.wav"));
    killedEnemy_.setSource(QUrl("qrc:/soundeffects/BugDead.wav"));
    hitGround_.setSource(QUrl("qrc:/soundeffects/hitGround.wav"));
    cheatOn_.setSource(QUrl("qrc:/soundeffects/cheatOn.wav"));
    cheatOff_.setSource(QUrl("qrc:/soundeffects/cheatOff.wav"));
    shoot_.setSource(QUrl("qrc:/soundeffects/shoot.wav"));
    shoot_.setVolume(0.5);
    dead_.setSource(QUrl("qrc:/soundeffects/dead.wav"));
    colWall_.setSource(QUrl("qrc:/soundeffects/colwall.wav"));
}

Sound::~Sound() {
    delete playlist;
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

void Sound::killedEnemy(){
    killedEnemy_.play();
}

void Sound::hitGround(){
    hitGround_.play();
}

void Sound::cheatOff(){
    cheatOff_.play();
}

void Sound::cheatOn(){
    cheatOn_.play();
}

void Sound::dead(){
    dead_.play();
}

void Sound::shoot(){
    shoot_.play();
}

void Sound::colWall(){
    colWall_.play();
}
