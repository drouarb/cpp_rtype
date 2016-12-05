//
// Created by celeriy on 05/12/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERHANDSHAKE_HH
#define CPP_RTYPE_CLIENTLISTENERHANDSHAKE_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketErrorHandshake.hh"
#include "IGameClient.hh"

namespace client {
    class ClientListenerErrorHandShake
            : public network::ListenerTemplate<network::packet::PacketErrorHandshake, network::packet::ERROR_HANDSHAKE> {

    public:
        ClientListenerErrorHandShake(IGameClient *gameClient);

        ~ClientListenerErrorHandShake();

        void notify(const network::packet::PacketErrorHandshake *packet);

    private:
        IGameClient *gameclient;
    };
}


#endif //CPP_RTYPE_CLIENTLISTENERHANDSHAKE_HH
