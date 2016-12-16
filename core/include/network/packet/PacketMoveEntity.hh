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
            PacketMoveEntity(uint32_t tick = 0,uint32_t eventId = 0, uint16_t entityId = 0, int16_t vecx = 0, int16_t vecy = 0, int16_t posx = 0, int16_t posy = 0);
            void setTick(uint32_t tick);
            uint32_t getTick() const;
            void setEventId(uint32_t id);
            uint32_t getEventId() const;
            void setEntityId(uint16_t entityId);
            uint16_t getEntityId() const;
            void setVecX(int16_t vecX);
            int16_t getVecX() const;
            void setVecY(int16_t vecY);
            int16_t getVecY() const;
            void setPosX(int16_t pos_x);
            int16_t  getPosX() const;
            void setPosY(int16_t pos_y);
            int16_t getPosY() const;
        };
    }
}


#endif //CPP_RTYPE_PACKETMOVEENTITY_HH
