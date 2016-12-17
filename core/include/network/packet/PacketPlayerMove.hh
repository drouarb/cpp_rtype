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
         PacketPlayerMove(uint32_t tick = 0, int16_t vect_x = 0, int16_t vect_y = 0, int16_t pos_x = 0, int16_t pos_y = 0);
         virtual  ~PacketPlayerMove();
         void setTick(uint32_t tick);
         uint32_t  getTick() const;
         void setVectX(int16_t vect_x);
         int16_t getVectX() const;
         void setVectY(int16_t vect_y);
         int16_t getVectY() const;
         void setPosX(int16_t pos_x);
         int16_t getPosX() const;
         void setPosY(int16_t pos_y);
         int16_t getPosY() const;
     };
 }
}


#endif //CPP_RTYPE_PACKETMOVEPLAYER_HH
