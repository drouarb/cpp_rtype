//
// Created by celeriy on 16/12/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERSYNCHRONISATION_HH
#define CPP_RTYPE_CLIENTLISTENERSYNCHRONISATION_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketSynchronization.hh"
#include "NetworkManager.hh"
namespace client {
    class ClientListenerSynchronization
            : public network::ListenerTemplate<network::packet::PacketSynchronization, network::packet::SYNCHRONIZATION> {

    public:
        ClientListenerSynchronization(NetworkManager *networkManager);

        ~ClientListenerSynchronization();

        void notify(const network::packet::PacketSynchronization *packet);

    private:
        NetworkManager *networkManager;
    };
}


#endif //CPP_RTYPE_CLIENTLISTENERGAMEDATA_HH
