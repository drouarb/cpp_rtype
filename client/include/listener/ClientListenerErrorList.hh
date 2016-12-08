//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERERRORLIST_HH
#define CPP_RTYPE_CLIENTLISTENERERRORLIST_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketErrorList.hh"
#include "NetworkManager.hh"
namespace client {
    class ClientListenerErrorList
            : public network::ListenerTemplate<network::packet::PacketErrorList, network::packet::ERROR_LIST> {

    public:
        ClientListenerErrorList(NetworkManager *networkManager);

        ~ClientListenerErrorList();

        void notify(const network::packet::PacketErrorList *packet);

    private:
        NetworkManager *networkManager;
    };
}

#endif //CPP_RTYPE_CLIENTLISTENERERRORLIST_HH
