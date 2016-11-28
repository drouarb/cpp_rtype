//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERGAMELIST_HH
#define CPP_RTYPE_CLIENTLISTENERGAMELIST_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketGameList.hh"
#include "IGameClient.hh"
class ClientListenerGameList : public network::ListenerTemplate<network::packet::PacketGameList, network::packet::GAME_LIST>
{
    class IGameClient;
public:
    ClientListenerGameList(IGameClient *gameClient);
    ~ClientListenerGameList();
    void notify(const network::packet::PacketGameList * packet);

private:
    IGameClient *gameclient;
};



#endif //CPP_RTYPE_CLIENTLISTENERGAMELIST_HH
