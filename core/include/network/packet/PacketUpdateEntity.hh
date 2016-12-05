//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETUPDATEENTITY_HH
#define CPP_RTYPE_PACKETUPDATEENTITY_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketUpdateEntity : public APacket {
            virtual ~PacketUpdateEntity();
            PacketUpdateEntity(uint32_t tick = 0,uint32_t eventId = 0, uint16_t entityId = 0, uint16_t hp = 0);
            void setTick(uint32_t tick);
            uint32_t getTick() const;
            void setEventId(uint16_t id);
            uint16_t getEventId() const;
            void setEntityId(uint16_t entityId);
            uint16_t getEntityId() const;
            void setHp(uint16_t hp);
            uint16_t getHp() const;


        };
    }
}

#endif //CPP_RTYPE_PACKETUPDATEENTITY_HH
