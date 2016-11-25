//
// Created by jonas_e on 11/25/16.
//

#ifndef CPP_RTYPE_IAUDIOMANAGER_HH
#define CPP_RTYPE_IAUDIOMANAGER_HH

#include <string>

namespace UI {
    class IAudioManager {
    public:
        ~IAudioManager(){};
        virtual int getVolume() = 0;
        virtual void setVolume(int newVolume) = 0;
        virtual void playSound(int soundID) = 0;
        virtual void playMusic(std::string path) = 0;
        virtual bool isPlaying() = 0;
        virtual int createPlaylist() = 0;
        virtual void addMusic(int playlistID) = 0;
    };
}


#endif //CPP_RTYPE_IAUDIOMANAGER_HH
