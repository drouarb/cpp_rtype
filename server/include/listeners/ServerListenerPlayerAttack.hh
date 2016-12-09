//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERPLAYERATTACK_HH
#define CPP_RTYPE_SERVERLISTENERPLAYERATTACK_HH

#include "IListenerHandler.hh"
#include <network/packet/PacketPlayerAttack.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerPlayerAttack : public network::ListenerTemplate<network::packet::PacketPlayerAttack, network::packet::PLAYER_ATTACK> {
    private:
        IListenerHandler *IListenerHandler;

    public:
        ServerListenerPlayerAttack();

        ServerListenerPlayerAttack(server::IListenerHandler *);

        void notify(const network::packet::PacketPlayerAttack *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERPLAYERATTACK_HH
