//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERSYNACK_HH
#define CPP_RTYPE_CLIENTLISTENERSYNACK_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketSynAck.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerSynAck
            : public network::ListenerTemplate<network::packet::PacketSynAck, network::packet::SYN_ACK> {

    public:
        ClientListenerSynAck(IGameClient *gameClient);

        ~ClientListenerSynAck();

        void notify(const network::packet::PacketSynAck *packet);

    private:
        IGameClient *gameclient;
    };

}
#endif //CPP_RTYPE_CLIENTLISTENERSYNACK_HH
