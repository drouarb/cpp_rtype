//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERASKLIST_HH
#define CPP_RTYPE_SERVERLISTENERASKLIST_HH

#include <network/packet/PacketAskList.hh>
#include <network/listener/ListenerTemplate.hpp>
#include "IListenerHandler.hh"

namespace server {

    class ServerListenerAskList : public network::ListenerTemplate<network::packet::PacketAskList, network::packet::ASK_LIST> {
    private:
        IListenerHandler *iListenerHandler;

    public:
        ServerListenerAskList(IListenerHandler *iListenerHandler);

        void notify(const network::packet::PacketAskList *packet);
    };

}


#endif //CPP_RTYPE_SERVERLISTENERASKLIST_HH
