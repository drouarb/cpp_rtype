//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETACK_HH
#define CPP_RTYPE_PACKETACK_HH

#include "network/packet/APacket.hh"
namespace network
{
    namespace packet {
        class PacketAck  :public APacket{
        public:
            PacketAck(uint16_t ack = 0);
            virtual ~PacketAck();
            void setAck(uint16_t ack);
            uint16_t getAck() const ;
        };
    }
}


#endif //CPP_RTYPE_PACKETACK_HH
