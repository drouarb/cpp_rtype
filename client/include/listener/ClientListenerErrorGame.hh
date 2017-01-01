//
// Created by celeriy on 01/01/17.
//

#ifndef CPP_RTYPE_CLIENTLISTENERERRORGAME_HH
#define CPP_RTYPE_CLIENTLISTENERERRORGAME_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketErrorGame.hh"
#include "NetworkManager.hh"

namespace client {
    class ClientListenerErrorGame
            : public network::ListenerTemplate<network::packet::PacketErrorGame, network::packet::ERROR_GAME> {

    public:
        ClientListenerErrorGame(NetworkManager *networkManager);

        ~ClientListenerErrorGame();

        void notify(const network::packet::PacketErrorGame *packet);

    private:
        NetworkManager *networkManager;
    };
}


#endif //CPP_RTYPE_CLIENTLISTENERERRORGAME_HH
