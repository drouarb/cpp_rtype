//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERDISCONNECT_HH
#define CPP_RTYPE_SERVERLISTENERDISCONNECT_HH

#include "IListenerHandler.hh"
#include <network/packet/PacketDisconnect.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerDisconnect : public network::ListenerTemplate<network::packet::PacketDisconnect, network::packet::DISCONNECT> {
    private:
        IListenerHandler *IListenerHandler;

    public:
        ServerListenerDisconnect(server::IListenerHandler *iListenerHandler);

        void notify(const network::packet::PacketDisconnect *packet);
    };

}
#endif //CPP_RTYPE_SERVERLISTENERDISCONNECT_HH
