//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERSPAWNENTITY_HH
#define CPP_RTYPE_CLIENTLISTENERSPAWNENTITY_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketSpawnEntity.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerSpawnEntity
            : public network::ListenerTemplate<network::packet::PacketSpawnEntity, network::packet::SPAWN_ENTITY> {

    public:
        ClientListenerSpawnEntity(IGameClient *gameClient);

        ~ClientListenerSpawnEntity();

        void notify(const network::packet::PacketSpawnEntity *packet);

    private:
        IGameClient *gameclient;
    };

}
#endif //CPP_RTYPE_CLIENTLISTENERSPAWNENTITY_HH
