//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERUPDATEENTITY_HH
#define CPP_RTYPE_CLIENTLISTENERUPDATEENTITY_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketUpdateEntity.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerUpdateEntity
            : public network::ListenerTemplate<network::packet::PacketUpdateEntity, network::packet::UPDATE_ENTITY> {

    public:
        ClientListenerUpdateEntity(IGameClient *gameClient);

        ~ClientListenerUpdateEntity();

        void notify(const network::packet::PacketUpdateEntity *packet);

    private:
        IGameClient *gameclient;
    };
}

#endif //CPP_RTYPE_CLIENTLISTENERUPDATEENTITY_HH
