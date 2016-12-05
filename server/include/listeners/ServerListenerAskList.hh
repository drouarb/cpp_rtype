//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERASKLIST_HH
#define CPP_RTYPE_SERVERLISTENERASKLIST_HH

#include <network/packet/PacketAskList.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerAskList : public network::ListenerTemplate<network::packet::PacketAskList, network::packet::ASK_LIST> {
    public:
        ServerListenerAskList();

        void notify(const network::packet::PacketAskList *packet);
    };

}


#endif //CPP_RTYPE_SERVERLISTENERASKLIST_HH
