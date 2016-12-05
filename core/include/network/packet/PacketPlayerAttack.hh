//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETPLAYERATTACK_HH
#define CPP_RTYPE_PACKETPLAYERATTACK_HH


#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketPlayerAttack : public  APacket{
        public:
            PacketPlayerAttack(uint32_t tick = 0, uint8_t attackId = 0);
            virtual  ~PacketPlayerAttack();
            void setTick(uint32_t tick);
            uint32_t  getTick() const;
            void setAttackId(uint8_t id);
            uint8_t getAttackId() const;
        };
    }
}



#endif //CPP_RTYPE_PACKETPLAYERATTACK_HH
