//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERQUIT_HH
#define CPP_RTYPE_SERVERLISTENERQUIT_HH

#include <network/packet/IPacket.hh>
#include <network/packet/PacketQuit.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerQuit : public network::ListenerTemplate<network::packet::PacketQuit, network::packet::QUIT> {
    public:
        ServerListenerQuit();

        void notify(const network::packet::PacketQuit *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERQUIT_HH
