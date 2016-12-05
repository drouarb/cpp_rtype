//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERSYN_HH
#define CPP_RTYPE_SERVERLISTENERSYN_HH


#include <network/packet/IPacket.hh>
#include <network/packet/PacketSyn.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerSyn : public network::ListenerTemplate<network::packet::PacketSyn, network::packet::SYN> {
    public:
        ServerListenerSyn();

        void notify(const network::packet::PacketSyn *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERSYN_HH
