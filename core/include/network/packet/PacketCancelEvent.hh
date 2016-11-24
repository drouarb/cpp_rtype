//
// Created by celeriy on 24/11/16.
//

#ifndef CPP_RTYPE_PACKETCANCELEVENT_HH
#define CPP_RTYPE_PACKETCANCELEVENT_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketCancelEvent : public APacket {
        public:
            PacketCancelEvent(uint32_t eventId = 0);
            virtual ~PacketCancelEvent();
            void setCancelEvent(uint32_t eventId);
            uint32_t getCancelEvent() const;
        };
    }
}


#endif //CPP_RTYPE_PACKETCANCELEVENT_HH
