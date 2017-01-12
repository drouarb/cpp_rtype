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
        PacketSpawnEntity(uint32_t tick = 0, uint32_t eventId = 0, const std::string &spriteName = "", uint32_t entityId = 0, int32_t pos_x = 0,
                                  int32_t pos_y = 0, int32_t hp = 0);
        virtual ~PacketSpawnEntity();
         void setTick(uint32_t tick);
         uint32_t getTick() const;
         void setEventId(uint32_t id);
         uint32_t getEventId() const;
         void setSpriteName(const std::string &msg);
         const utils::NetworkString &getSpriteName() const;
         void setEntityId(uint32_t entityId);
         uint32_t getEntityId() const;
         void setPosX(int32_t pos_x);
         int32_t getPosX() const;
         void setPosY(int32_t pos_y);
         int32_t getPosY() const;
         void setHp(int32_t hp);
         int32_t getHp() const;
     };
 }
}


#endif //CPP_RTYPE_PACKETSPAWNENTITY_HH
