//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERCANCELEVENT_HH
#define CPP_RTYPE_CLIENTLISTENERCANCELEVENT_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketCancelEvent.hh"
#include "GameClient.hh"
namespace client {
    class ClientListenerCancelEvent
            : public network::ListenerTemplate<network::packet::PacketCancelEvent, network::packet::CANCEL_EVENT> {

    public:
        ClientListenerCancelEvent(GameClient *gameClient);

        ~ClientListenerCancelEvent();

        void notify(const network::packet::PacketCancelEvent *packet);

    private:
        GameClient *gameclient;
    };

}
#endif //CPP_RTYPE_CLIENTLISTENERCANCELEVENT_HH
