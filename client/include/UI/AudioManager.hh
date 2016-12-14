//
// Created by jonas_e on 11/25/16.
//

#ifndef CPP_RTYPE_AUDIOMANAGER_HH
#define CPP_RTYPE_AUDIOMANAGER_HH

#include <SFML/Audio.hpp>
#include "IAudioManager.hh"

namespace UI {
    class AudioManager : public IAudioManager {
    public:
        AudioManager();

        int getVolume();
        void setVolume(int newVolume);
        void playSound(int soundID);
        void playMusic(std::string path);
        bool isPlaying();
        int createPlaylist();
        void addMusic(int playlistID);
    private:
        sf::Music music;
        int volume;
    };
}

#endif //CPP_RTYPE_AUDIOMANAGER_HH
