//
// Created by celeriy on 19/12/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERPLAYERDATA_HH
#define CPP_RTYPE_CLIENTLISTENERPLAYERDATA_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketPlayerData.hh"
#include "NetworkManager.hh"
namespace client {
    class ClientListenerPlayerData
            : public network::ListenerTemplate<network::packet::PacketPlayerData, network::packet::PLAYER_DATA> {

    public:
        ClientListenerPlayerData(NetworkManager *networkManager);

        ~ClientListenerPlayerData();

        void notify(const network::packet::PacketPlayerData *packet);

    private:
        NetworkManager *networkManager;
    };
}


#endif //CPP_RTYPE_CLIENTLISTENERPLAYERDATA_HH
