//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETPLAYSOUND_HH
#define CPP_RTYPE_PACKETPLAYSOUND_HH

#include <network/utils/NetworkString.hh>
#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketPlaySound : public APacket {
        public:
            virtual ~PacketPlaySound();
            PacketPlaySound(uint32_t tick = 0, uint32_t eventId = 0, const std::string &SoundName = "");
            void setTick(uint32_t tick);
            uint32_t getTick() const;
            void setEventId(uint32_t id);
            uint32_t getEventId() const;
            void setSoundName(const std::string &SoundName);
            utils::NetworkString getSoundName() const;
        };
    }
}

#endif //CPP_RTYPE_PACKETPLAYSOUND_HH
