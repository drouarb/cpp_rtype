//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERQUIT_HH
#define CPP_RTYPE_SERVERLISTENERQUIT_HH

#include <network/packet/IPacket.hh>
#include <network/packet/PacketQuit.hh>
#include <network/listener/ListenerTemplate.hpp>
#include "IListenerHandler.hh"

namespace server {

    class ServerListenerQuit : public network::ListenerTemplate<network::packet::PacketQuit, network::packet::QUIT> {
    private:
        IListenerHandler * listenerHandler;

    public:
        ServerListenerQuit();

        ServerListenerQuit(server::IListenerHandler * listenerHandler);

        void notify(const network::packet::PacketQuit *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERQUIT_HH
