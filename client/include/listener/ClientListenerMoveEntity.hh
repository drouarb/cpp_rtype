//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH
#define CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketMoveEntity.hh"
#include "NetworkManager.hh"
namespace client {
    class ClientListenerMoveEntity
            : public network::ListenerTemplate<network::packet::PacketMoveEntity, network::packet::MOVE_ENTITY> {

    public:
        ClientListenerMoveEntity(NetworkManager *networkManager);

        ~ClientListenerMoveEntity();

        void notify(const network::packet::PacketMoveEntity *packet);

    private:
        NetworkManager *networkManager;
    };
}

#endif //CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH
