//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETGAMELIST_HH
#define CPP_RTYPE_PACKETGAMELIST_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketGameList : public APacket {
        public:
            PacketGameList(std::vector<std::pair<uint8_t, uint16_t >> GameList = {});
            virtual ~PacketGameList();
            std::vector<std::pair<uint8_t, uint16_t >> getGameList() const;
        };
    }
}

#endif //CPP_RTYPE_PACKETGAMELIST_HH
