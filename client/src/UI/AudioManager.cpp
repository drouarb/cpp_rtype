//
// Created by jonas_e on 11/25/16.
//

#include <iostream>
#include "../../include/UI/AudioManager.hh"

UI::AudioManager::AudioManager() {
    volume = 100;
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
