//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETPLAYSOUND_HH
#define CPP_RTYPE_PACKETPLAYSOUND_HH

#include <network/packet/APacket.hh>
#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketPlaySound : public APacket {
        public:
            virtual ~PacketPlaySound();
            PacketPlaySound(uint32_t tick = 0,uint32_t eventId = 0, uint16_t SoundName = 0);
            void setTick(uint32_t tick);
            uint32_t getTick() const;
            void setEventId(uint16_t id);
            uint16_t getEventId() const;
            void setSoundName(uint16_t SoundName);
            uint16_t getSoundName() const;
        };
    }
}

#endif //CPP_RTYPE_PACKETPLAYSOUND_HH
