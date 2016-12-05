//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERJOIN_HH
#define CPP_RTYPE_SERVERLISTENERJOIN_HH

#include <network/packet/PacketJoin.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerJoin : public network::ListenerTemplate<network::packet::PacketJoin, network::packet::JOIN> {
    public:
        ServerListenerJoin();

        void notify(const network::packet::PacketJoin *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERJOIN_HH
