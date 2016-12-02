//
// Created by celeriy on 28/11/16.
//

#ifndef CPP_RTYPE_CLIENTLISTENERLEADERBOARD_HH
#define CPP_RTYPE_CLIENTLISTENERLEADERBOARD_HH

#include <network/listener/ListenerTemplate.hpp>
#include "network/packet/PacketLeaderBoard.hh"
#include "IGameClient.hh"
namespace client {
    class ClientListenerLeaderBoard
            : public network::ListenerTemplate<network::packet::PacketLeaderBoard, network::packet::LEADER_BOARD> {

    public:
        ClientListenerLeaderBoard(IGameClient *gameClient);

        ~ClientListenerLeaderBoard();

        void notify(const network::packet::PacketLeaderBoard *packet);

    private:
        IGameClient *gameclient;
    };
}





#endif //CPP_RTYPE_CLIENTLISTENERLEADERBOARD_HH
