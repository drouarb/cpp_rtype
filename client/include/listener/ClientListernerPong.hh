//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTERNERPONG_HH
#define CPP_RTYPE_CLIENTLISTERNERPONG_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketPong.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerPong : public network::ListenerTemplate<network::packet::PacketPong, network::packet::PONG> {
    public:
        ClientListenerPong(IGameClient *gameClient);

        ~ClientListenerPong();

        void notify(const network::packet::PacketPong *packet);

    private:
        IGameClient *gameclient;
    };
}


#endif //CPP_RTYPE_CLIENTLISTERNERPONG_HH
