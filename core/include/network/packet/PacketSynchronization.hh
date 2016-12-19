/*
** trouve_b
*/

#ifndef CPP_RTYPE_PACKETSYNCRO_HH
#define CPP_RTYPE_PACKETSYNCRO_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketSynchronization : public APacket {
        public:
            PacketSynchronization(uint32_t tick = 0, int64_t time = 0);
            virtual ~PacketSynchronization();
            void setTick(uint32_t tick);
            uint32_t  getTick() const;
            void setTime(int64_t time);
            int64_t getTime() const;
        };
    }
}


#endif //CPP_RTYPE_PACKETSYNCRONISATION_HH
