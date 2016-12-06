//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETASKLEADERBOARD_HH
#define CPP_RTYPE_PACKETASKLEADERBOARD_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketAskLeaderBoard  : public APacket{
        public:
            PacketAskLeaderBoard();
            virtual ~PacketAskLeaderBoard();
        };
    }
}


#endif //CPP_RTYPE_PACKETASKLEADERBOARD_HH
