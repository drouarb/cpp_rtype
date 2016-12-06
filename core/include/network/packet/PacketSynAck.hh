//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETSYNACK_HH
#define CPP_RTYPE_PACKETSYNACK_HH

#include <network/packet/APacket.hh>

namespace network {
 namespace packet {
     class PacketSynAck : public APacket{
     public:
         PacketSynAck(uint16_t syn = 0, uint16_t ack = 0);
         virtual ~PacketSynAck();
         void setAck(uint16_t ack);
         void setSyn(uint16_t syn);
         uint16_t getAck() const;
         uint16_t getSyn() const;
     };
 }
}


#endif //CPP_RTYPE_PACKETSYNACK_HH
