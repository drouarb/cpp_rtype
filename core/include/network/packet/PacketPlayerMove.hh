//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETMOVEPLAYER_HH
#define CPP_RTYPE_PACKETMOVEPLAYER_HH

#include <network/packet/APacket.hh>

namespace network {
 namespace packet {
     class PacketPlayerMove : public  APacket{
     public:
         PacketPlayerMove(uint32_t tick = 0, uint16_t vect_x = 0, uint16_t vect_y = 0);
         virtual  ~PacketPlayerMove();
         void setTick(uint32_t tick);
         uint32_t  getTick() const;
         void setVectX(uint16_t vect_x);
         uint16_t getVectX() const;
         void setVectY(uint16_t vect_y);
         uint16_t getVectY() const;
     };
 }
}


#endif //CPP_RTYPE_PACKETMOVEPLAYER_HH
