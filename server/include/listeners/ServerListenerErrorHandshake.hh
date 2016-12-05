//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERERRORHANDSHAKE_HH
#define CPP_RTYPE_SERVERLISTENERERRORHANDSHAKE_HH


#include <network/listener/IPacketListener.hh>
#include <network/packet/PacketErrorHandshake.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerErrorHandshake : public network::ListenerTemplate<network::packet::PacketErrorHandshake, network::packet::ERROR_HANDSHAKE> {
    public:
        ServerListenerErrorHandshake();

        void notify(const network::packet::PacketErrorHandshake *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERERRORHANDSHAKE_HH
