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
            PacketMoveEntity(uint32_t tick = 0,uint32_t eventId = 0, uint32_t entityId = 0, int32_t vecx = 0, int32_t vecy = 0, int32_t posx = 0, int32_t posy = 0);
            void setTick(uint32_t tick);
            uint32_t getTick() const;
            void setEventId(uint32_t id);
            uint32_t getEventId() const;
            void setEntityId(uint32_t entityId);
            uint32_t getEntityId() const;
            void setVecX(int32_t vecX);
            int32_t getVecX() const;
            void setVecY(int32_t vecY);
            int32_t getVecY() const;
            void setPosX(int32_t pos_x);
            int32_t  getPosX() const;
            void setPosY(int32_t pos_y);
            int32_t getPosY() const;
        };
    }
}


#endif //CPP_RTYPE_PACKETMOVEENTITY_HH
