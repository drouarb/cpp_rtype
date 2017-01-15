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
         PacketPlayerMove(uint32_t tick = 0, int32_t vect_x = 0, int32_t vect_y = 0, int32_t pos_x = 0, int32_t pos_y = 0);
         virtual  ~PacketPlayerMove();
         void setTick(uint32_t tick);
         uint32_t  getTick() const;
         void setVectX(int32_t vect_x);
         int32_t getVectX() const;
         void setVectY(int32_t vect_y);
         int32_t getVectY() const;
         void setPosX(int32_t pos_x);
         int32_t getPosX() const;
         void setPosY(int32_t pos_y);
         int32_t getPosY() const;
     };
 }
}


#endif //CPP_RTYPE_PACKETMOVEPLAYER_HH
