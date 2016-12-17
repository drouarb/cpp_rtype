//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH
#define CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketMoveEntity.hh"
#include "GameClient.hh"
namespace client {
    class ClientListenerMoveEntity
            : public network::ListenerTemplate<network::packet::PacketMoveEntity, network::packet::MOVE_ENTITY> {

    public:
        ClientListenerMoveEntity(GameClient *gameClient);

        ~ClientListenerMoveEntity();

        void notify(const network::packet::PacketMoveEntity *packet);

    private:
        GameClient *gameclient;
    };
}

#endif //CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH
