//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERERRORLIST_HH
#define CPP_RTYPE_CLIENTLISTENERERRORLIST_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketErrorList.hh"
#include "GameClient.hh"
namespace client {
    class ClientListenerErrorList
            : public network::ListenerTemplate<network::packet::PacketErrorList, network::packet::ERROR_LIST> {

    public:
        ClientListenerErrorList(GameClient *gameClient);

        ~ClientListenerErrorList();

        void notify(const network::packet::PacketErrorList *packet);

    private:
        GameClient *gameclient;
    };
}

#endif //CPP_RTYPE_CLIENTLISTENERERRORLIST_HH
