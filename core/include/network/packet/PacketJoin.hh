//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETJOIN_HH
#define CPP_RTYPE_PACKETJOIN_HH


#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketJoin : public APacket {
        public:
            PacketJoin(uint8_t roomId = 0);
            virtual ~PacketJoin();
            void setJoin(uint8_t roomdId);
            uint8_t getJoin() const;
        };
    }
}

#endif //CPP_RTYPE_PACKETJOIN_HH
