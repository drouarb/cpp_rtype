//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH
#define CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketDisconnect.hh"
#include "IGameClient.hh"
namespace client {
class ClientListenerDisconnect : public network::ListenerTemplate<network::packet::PacketDisconnect, network::packet::DISCONNECT>
{
public:
    ClientListenerDisconnect(IGameClient *gameClient);
    ~ClientListenerDisconnect();
    void notify(const network::packet::PacketDisconnect * packet);

private:
    IGameClient *gameclient;
};
}

#endif //CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH
