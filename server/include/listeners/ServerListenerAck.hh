//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERACK_HH
#define CPP_RTYPE_SERVERLISTENERACK_HH

#include <network/packet/PacketAck.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerAck : public network::ListenerTemplate<network::packet::PacketAck, network::packet::ACK> {
    public:
        ServerListenerAck();

        void notify(const network::packet::PacketAck *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERACK_HH
