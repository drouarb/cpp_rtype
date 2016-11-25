//
// Created by jonas_e on 11/25/16.
//

#include <iostream>
#include "../../include/UI/AudioManager.hh"

UI::AudioManager::AudioManager() {
    volume = 100;
}

void UI::AudioManager::playSound(int soundID) {

}

bool UI::AudioManager::isPlaying() {
    return music.getStatus() == sf::SoundSource::Status::Playing;
}

void UI::AudioManager::playMusic(std::string path) {
    if (music.openFromFile(path)) {
        music.setVolume(volume);
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
    volume = newVolume;
    if (music.getStatus() == sf::SoundSource::Status::Playing)
        music.setVolume(newVolume);
}

int UI::AudioManager::getVolume() {
    return volume;
}
