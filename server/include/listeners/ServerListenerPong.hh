//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERPONG_HH
#define CPP_RTYPE_SERVERLISTENERPONG_HH

#include <network/packet/PacketPong.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerPong : public network::ListenerTemplate<network::packet::PacketPong, network::packet::PONG> {
    public:
        ServerListenerPong();

        void notify(const network::packet::PacketPong *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERPONG_HH
