//
// Created by celeriy on 16/12/16.
//

#ifndef CPP_RTYPE_PACKETGAMEDATA_HH
#define CPP_RTYPE_PACKETGAMEDATA_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketGameData : public APacket {
        public:
            PacketGameData(uint32_t tick = 0, int64_t time = 0);
            virtual ~PacketGameData();
            void setTick(uint32_t tick);
            uint32_t  getTick() const;
            void setTime(int64_t time);
            int64_t getTime() const;
        };
    }
}


#endif //CPP_RTYPE_PACKETGAMEDATA_HH
