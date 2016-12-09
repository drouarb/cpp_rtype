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
        IListenerHandler *IListenerHandler;

    public:
        ServerListenerRegister();

        ServerListenerRegister(server::IListenerHandler *IListenerHandler);

        void notify(const network::packet::PacketRegister *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERREGISTER_HH
