//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERPLAYSOUND_HH
#define CPP_RTYPE_CLIENTLISTENERPLAYSOUND_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketPlaySound.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerPlaySound
            : public network::ListenerTemplate<network::packet::PacketPlaySound, network::packet::PLAY_SOUND> {

    public:
        ClientListenerPlaySound(IGameClient *gameClient);

        ~ClientListenerPlaySound();

        void notify(const network::packet::PacketPlaySound *packet);

    private:
        IGameClient *gameclient;
    };
}
#endif //CPP_RTYPE_CLIENTLISTENERPLAYSOUND_HH
