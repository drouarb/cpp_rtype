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
        ~AudioManager();

        int getVolume();
        void setVolume(int newVolume);
        int addSound(std::string path);
        void playSound(int soundID);
        void playMusic(std::string path);
        void stopMusic();
        bool isPlaying();
        int createPlaylist();
        void addMusic(int playlistID);
    private:
        sf::Music music;
        sf::Sound sound;
        std::vector<sf::SoundBuffer*> buffers;
        int volume;
    };
}

#endif //CPP_RTYPE_AUDIOMANAGER_HH
