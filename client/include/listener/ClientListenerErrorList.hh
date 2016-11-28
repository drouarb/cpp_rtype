//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERERRORLIST_HH
#define CPP_RTYPE_CLIENTLISTENERERRORLIST_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketErrorList.hh"
#include "IGameClient.hh"

class ClientListenerErrorList : public network::ListenerTemplate<network::packet::PacketErrorList, network::packet::ERROR_LIST>
{
    class IGameClient;
public:
    ClientListenerErrorList(IGameClient *gameClient);
    ~ClientListenerErrorList();
    void notify(const network::packet::PacketErrorList * packet);

private:
    IGameClient *gameclient;
};



#endif //CPP_RTYPE_CLIENTLISTENERERRORLIST_HH
