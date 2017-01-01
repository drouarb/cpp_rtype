//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH
#define CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH


#include <network/listener/ISocketDisconnectionListener.hh>
#include "network/packet/PacketDisconnect.hh"
#include "NetworkManager.hh"
namespace client {
class ClientListenerDisconnect : public network::listener::ISocketDisconnectionListener
{
public:
    ClientListenerDisconnect(NetworkManager *networkManager);
    ~ClientListenerDisconnect();
    void notify(unsigned  long fd);

private:
    NetworkManager *networkManager;
};
}

#endif //CPP_RTYPE_CLIENTLISTENERDISCONNECT_HH
