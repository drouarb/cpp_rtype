//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETLEADERBOARD_HH
#define CPP_RTYPE_PACKETLEADERBOARD_HH


#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketLeaderBoard : public APacket {
        public:
            PacketLeaderBoard(std::vector<std::pair<uint32_t, std::string>> LeaderBoard = {});
            virtual ~PacketLeaderBoard();

            std::vector<std::pair<uint32_t, std::string>> getLeaderBoard() const;
        };
    }
}

#endif //CPP_RTYPE_PACKETLEADERBOARD_HH
