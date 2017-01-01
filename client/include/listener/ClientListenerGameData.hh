//
// Created by celeriy on 01/01/17.
//

#ifndef CPP_RTYPE_CLIENTLISTENERGAMEDATA_HH
#define CPP_RTYPE_CLIENTLISTENERGAMEDATA_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketGameData.hh"
#include "NetworkManager.hh"

namespace client {
    class ClientListenerGameData
            : public network::ListenerTemplate<network::packet::PacketGameData, network::packet::GAME_DATA> {

    public:
        ClientListenerGameData(NetworkManager *networkManager);

        ~ClientListenerGameData();

        void notify(const network::packet::PacketGameData *packet);

    private:
        NetworkManager *networkManager;
    };
}



#endif //CPP_RTYPE_CLIENTLISTENERGAMEDATA_HH
