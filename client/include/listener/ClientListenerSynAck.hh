//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERSYNACK_HH
#define CPP_RTYPE_CLIENTLISTENERSYNACK_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketSynAck.hh"
#include "GameClient.hh"
namespace client {
    class ClientListenerSynAck
            : public network::ListenerTemplate<network::packet::PacketSynAck, network::packet::SYN_ACK> {

    public:
        ClientListenerSynAck(GameClient *gameClient);

        ~ClientListenerSynAck();

        void notify(const network::packet::PacketSynAck *packet);

    private:
        GameClient *gameclient;
    };

}
#endif //CPP_RTYPE_CLIENTLISTENERSYNACK_HH
