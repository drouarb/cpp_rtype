//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETMOVEENTITY_HH
#define CPP_RTYPE_PACKETMOVEENTITY_HH


#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketMoveEntity : public APacket {
        public:
            virtual ~PacketMoveEntity();
            PacketMoveEntity(uint32_t tick = 0,uint32_t eventId = 0, uint16_t entityId = 0, uint16_t vecx = 0, uint16_t vecy = 0);
            void setTick(uint32_t tick);
            uint32_t getTick() const;
            void setEventId(uint16_t id);
            uint16_t getEventId() const;
            void setEntityId(uint16_t entityId);
            uint16_t getEntityId() const;
            void setVecX(uint16_t vecX);
            uint16_t getVecX() const;
            void setVecY(uint16_t vecY);
            uint16_t getVecY() const;
        };
    }
}


#endif //CPP_RTYPE_PACKETMOVEENTITY_HH
