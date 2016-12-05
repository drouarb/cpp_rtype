//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERDISCONNECT_HH
#define CPP_RTYPE_SERVERLISTENERDISCONNECT_HH

#include <network/packet/PacketDisconnect.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerDisconnect : public network::ListenerTemplate<network::packet::PacketDisconnect, network::packet::DISCONNECT> {
    public:
        ServerListenerDisconnect();

        void notify(const network::packet::PacketDisconnect *packet);
    };

}
#endif //CPP_RTYPE_SERVERLISTENERDISCONNECT_HH
