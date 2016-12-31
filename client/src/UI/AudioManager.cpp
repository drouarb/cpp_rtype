//
// Created by jonas_e on 11/25/16.
//

#include <iostream>
#include <stdlib.h>
#include "../../include/UI/AudioManager.hh"

std::vector<std::string> menuSoundsPath {
        "media/musics/00.ogg",
        "media/musics/01.ogg",
        "media/musics/02.ogg",
        "media/musics/03.ogg",
        "media/musics/04.ogg",
        "media/musics/05.ogg",
        "media/musics/06.ogg",
        "media/musics/07.ogg",
        "media/musics/08.ogg",
        "media/musics/09.ogg",
        "media/musics/10.ogg",
        "media/musics/11.ogg",
        "media/musics/12.ogg",
        "media/musics/13.ogg",
        "media/musics/14.ogg",
        "media/musics/15.ogg",
        "media/musics/16.ogg",
        "media/musics/17.ogg",
        "media/musics/18.ogg",
        "media/musics/19.ogg",
        "media/musics/20.ogg",
        "media/musics/21.ogg",
        "media/musics/22.ogg",
        "media/musics/23.ogg",
        "media/musics/24.ogg",
        "media/musics/25.ogg",
        "media/musics/26.ogg",
        "media/musics/27.ogg",
        "media/musics/28.ogg",
        "media/musics/29.ogg",
        "media/musics/30.ogg",
};

UI::AudioManager::AudioManager() {
    volume = 100;
    initMenuSound();
    srand(time(NULL));
}

UI::AudioManager::~AudioManager() {
    music.~Music();
    sound.~Sound();
}

void UI::AudioManager::playSound(int soundID) {
    sound.setBuffer(*(buffers[soundID]));
    sound.play();
}

bool UI::AudioManager::isPlaying() {
    return music.getStatus() == sf::SoundSource::Status::Playing;
}

void UI::AudioManager::playMusic(std::string path) {
    if (music.openFromFile(path)) {
        music.setVolume(volume);
        music.setLoop(true);
        music.play();
    } else {
        std::cerr << "Failed to load: " << path << std::endl;
    }
}

int UI::AudioManager::createPlaylist() {
    return 0;
}

void UI::AudioManager::addMusic(int playlistID) {

}

void UI::AudioManager::setVolume(int newVolume) {
    volume = newVolume > 100 ? 100 : newVolume < 0 ? 0 : newVolume;
    if (music.getStatus() == sf::SoundSource::Status::Playing)
        music.setVolume(newVolume);
    sound.setVolume(newVolume);
}

int UI::AudioManager::getVolume() {
    return volume;
}

int UI::AudioManager::addSound(std::string path) {
    sf::SoundBuffer *soundBuffer = new sf::SoundBuffer();
    soundBuffer->loadFromFile(path);
    buffers.push_back(soundBuffer);
    return static_cast<int>(buffers.size() - 1);
}

void UI::AudioManager::stopMusic() {
    music.stop();
}

void UI::AudioManager::initMenuSound() {
    for (auto path : menuSoundsPath) {
        addSound(path);
    }
}

void UI::AudioManager::playMenuSound() {
    playSound(rand() % 31);
}
