//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERGAMELIST_HH
#define CPP_RTYPE_CLIENTLISTENERGAMELIST_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketGameList.hh"
#include "NetworkManager.hh"
namespace client {
    class ClientListenerGameList
            : public network::ListenerTemplate<network::packet::PacketGameList, network::packet::GAME_LIST> {

    public:
        ClientListenerGameList(NetworkManager *networkManager);

        ~ClientListenerGameList();

        void notify(const network::packet::PacketGameList *packet);

    private:
        NetworkManager *networkManager;
    };
}



#endif //CPP_RTYPE_CLIENTLISTENERGAMELIST_HH
