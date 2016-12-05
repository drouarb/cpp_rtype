//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERDELETEENTITY_HH
#define CPP_RTYPE_CLIENTLISTENERDELETEENTITY_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketDeleteEntity.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerDeleteEntity
            : public network::ListenerTemplate<network::packet::PacketDeleteEntity, network::packet::DELETE_ENTITY> {

    public:
        ClientListenerDeleteEntity(IGameClient *gameClient);

        ~ClientListenerDeleteEntity();

        void notify(const network::packet::PacketDeleteEntity *packet);

    private:
        IGameClient *gameclient;
    };
}

#endif //CPP_RTYPE_CLIENTLISTENERDELETEENTITY_HH
