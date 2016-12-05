//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH
#define CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketMoveEntity.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerMoveEntity
            : public network::ListenerTemplate<network::packet::PacketMoveEntity, network::packet::MOVE_ENTITY> {

    public:
        ClientListenerMoveEntity(IGameClient *gameClient);

        ~ClientListenerMoveEntity();

        void notify(const network::packet::PacketMoveEntity *packet);

    private:
        IGameClient *gameclient;
    };
}

#endif //CPP_RTYPE_CLIENTLISTENERMOVEENTITY_HH
