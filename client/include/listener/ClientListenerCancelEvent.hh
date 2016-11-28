//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERCANCELEVENT_HH
#define CPP_RTYPE_CLIENTLISTENERCANCELEVENT_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketCancelEvent.hh"
#include "IGameClient.hh"
class ClientListenerCancelEvent : public network::ListenerTemplate<network::packet::PacketCancelEvent, network::packet::CANCEL_EVENT>
{
    class IGameClient;
public:
    ClientListenerCancelEvent(IGameClient *gameClient);
    ~ClientListenerCancelEvent();
    void notify(const network::packet::PacketCancelEvent * packet);

private:
    IGameClient *gameclient;
};


#endif //CPP_RTYPE_CLIENTLISTENERCANCELEVENT_HH
