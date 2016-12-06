//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTERNERPONG_HH
#define CPP_RTYPE_CLIENTLISTERNERPONG_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketPong.hh"
#include "GameClient.hh"
namespace client {
    class ClientListenerPong : public network::ListenerTemplate<network::packet::PacketPong, network::packet::PONG> {
    public:
        ClientListenerPong(GameClient *gameClient);

        ~ClientListenerPong();

        void notify(const network::packet::PacketPong *packet);

    private:
        GameClient *gameclient;
    };
}


#endif //CPP_RTYPE_CLIENTLISTERNERPONG_HH
