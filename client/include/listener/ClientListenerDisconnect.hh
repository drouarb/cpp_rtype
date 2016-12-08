//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH
#define CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH


#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketDisconnect.hh"
#include "NetworkManager.hh"
namespace client {
class ClientListenerDisconnect : public network::ListenerTemplate<network::packet::PacketDisconnect, network::packet::DISCONNECT>
{
public:
    ClientListenerDisconnect(NetworkManager *networkManager);
    ~ClientListenerDisconnect();
    void notify(const network::packet::PacketDisconnect * packet);

private:
    NetworkManager *networkManager;
};
}

#endif //CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH
