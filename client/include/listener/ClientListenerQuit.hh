//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERQUIT_HH
#define CPP_RTYPE_CLIENTLISTENERQUIT_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketQuit.hh"
#include "NetworkManager.hh"
namespace client {
    class ClientListenerQuit : public network::ListenerTemplate<network::packet::PacketQuit, network::packet::QUIT> {

    public:
        ClientListenerQuit(NetworkManager *networkManager);

        ~ClientListenerQuit();

        void notify(const network::packet::PacketQuit *packet);

    private:
        NetworkManager *networkManager;
    };
}


#endif //CPP_RTYPE_CLIENTLISTENERQUIT_HH
