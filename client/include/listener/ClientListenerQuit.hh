//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERQUIT_HH
#define CPP_RTYPE_CLIENTLISTENERQUIT_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketQuit.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerQuit : public network::ListenerTemplate<network::packet::PacketQuit, network::packet::QUIT> {

    public:
        ClientListenerQuit(IGameClient *gameClient);

        ~ClientListenerQuit();

        void notify(const network::packet::PacketQuit *packet);

    private:
        IGameClient *gameclient;
    };
}


#endif //CPP_RTYPE_CLIENTLISTENERQUIT_HH
