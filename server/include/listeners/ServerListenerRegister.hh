//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERREGISTER_HH
#define CPP_RTYPE_SERVERLISTENERREGISTER_HH

#include <network/packet/IPacket.hh>
#include <network/packet/PacketRegister.hh>
#include <network/listener/ListenerTemplate.hpp>
#include "IListenerHandler.hh"

namespace server {

    class ServerListenerRegister : public network::ListenerTemplate<network::packet::PacketRegister, network::packet::REGISTER> {
    private:
        IListenerHandler * listenerHandler;

    public:
        ServerListenerRegister();

        ServerListenerRegister(server::IListenerHandler * listenerHandler);

        void notify(const network::packet::PacketRegister *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERREGISTER_HH
