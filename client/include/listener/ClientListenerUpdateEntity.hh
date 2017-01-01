//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERUPDATEENTITY_HH
#define CPP_RTYPE_CLIENTLISTENERUPDATEENTITY_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketUpdateEntity.hh"
#include "NetworkManager.hh"
namespace client {
    class ClientListenerUpdateEntity
            : public network::ListenerTemplate<network::packet::PacketUpdateEntity, network::packet::UPDATE_ENTITY> {

    public:
        ClientListenerUpdateEntity(NetworkManager *networkManager);

        ~ClientListenerUpdateEntity();

        void notify(const network::packet::PacketUpdateEntity *packet);

    private:
        NetworkManager *networkManager;
    };
}

#endif //CPP_RTYPE_CLIENTLISTENERUPDATEENTITY_HH
