//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERPONG_HH
#define CPP_RTYPE_SERVERLISTENERPONG_HH

#include <network/packet/PacketPong.hh>
#include <network/listener/ListenerTemplate.hpp>
#include "IListenerHandler.hh"

namespace server {

    class ServerListenerPong : public network::ListenerTemplate<network::packet::PacketPong, network::packet::PONG> {
    private:
        IListenerHandler *IListenerHandler;

    public:

        ServerListenerPong(server::IListenerHandler *IListenerHandler);

        void notify(const network::packet::PacketPong *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERPONG_HH
