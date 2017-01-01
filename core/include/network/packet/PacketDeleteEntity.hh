//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETDELETEENTITY_HH
#define CPP_RTYPE_PACKETDELETEENTITY_HH


#include <network/packet/APacket.hh>

namespace network {
 namespace packet {
     class PacketDeleteEntity : public APacket {
     public:
        virtual ~PacketDeleteEntity();
        PacketDeleteEntity(uint32_t tick = 0,uint32_t eventId = 0, uint32_t entityId = 0);
         void setTick(uint32_t tick);
         uint32_t getTick() const;
         void setEventId(uint32_t id);
         uint32_t getEventId() const;
         void setEntityId(uint32_t entityId);
         uint32_t getEntityId() const;
     };
 }
}


#endif //CPP_RTYPE_PACKETDELETEENTITY_HH
