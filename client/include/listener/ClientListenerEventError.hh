//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENEREVENTERROR_HH
#define CPP_RTYPE_CLIENTLISTENEREVENTERROR_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketEventError.hh"
#include "GameClient.hh"
namespace client {
    class ClientListenerEventError
            : public network::ListenerTemplate<network::packet::PacketEventError, network::packet::EVENT_ERROR> {

    public:
        ClientListenerEventError(GameClient *gameClient);

        ~ClientListenerEventError();

        void notify(const network::packet::PacketEventError *packet);

    private:
        GameClient *gameclient;
    };
}
#endif //CPP_RTYPE_CLIENTLISTENEREVENTERROR_HH
