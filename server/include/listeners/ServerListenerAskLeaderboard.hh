//
// Created by greg on 05/12/2016.
//

#ifndef CPP_RTYPE_SERVERLISTENERASKLEADERBOARD_HH
#define CPP_RTYPE_SERVERLISTENERASKLEADERBOARD_HH

#include <network/packet/PacketAskLeaderBoard.hh>
#include <network/listener/ListenerTemplate.hpp>

namespace server {

    class ServerListenerAskLeaderboard : public network::ListenerTemplate<network::packet::PacketAskLeaderBoard, network::packet::ASK_LEADERBOARD> {
    public:
        ServerListenerAskLeaderboard();

        void notify(const network::packet::PacketAskLeaderBoard *packet);
    };

}

#endif //CPP_RTYPE_SERVERLISTENERASKLEADERBOARD_HH
