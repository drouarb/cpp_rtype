//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETSPAWNENTITY_HH
#define CPP_RTYPE_PACKETSPAWNENTITY_HH

#include <network/packet/APacket.hh>

namespace network {
 namespace packet {
     class PacketSpawnEntity  : public APacket{
     public:
        PacketSpawnEntity(uint32_t tick = 0, uint32_t eventId = 0, const std::string &spriteName = "", uint16_t entityId = 0, uint16_t pos_x = 0, uint16_t pos_y = 0);
        virtual ~PacketSpawnEntity();
         void setTick(uint32_t tick);
         uint32_t getTick() const;
         void setEventId(uint32_t id);
         uint32_t getEventId() const;
         void setSpriteName(const std::string &msg);
         const utils::NetworkString &getSpriteName() const;
         void setEntityId(uint16_t entityId);
         uint16_t getEntityId() const;
         void setPosX(uint16_t pos_x);
         uint16_t getPosX() const;
         void setPosY(uint16_t pos_y);
         uint16_t getPosY() const;
     };
 }
}


#endif //CPP_RTYPE_PACKETSPAWNENTITY_HH
