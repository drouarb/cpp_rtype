//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETASKLIST_HH
#define CPP_RTYPE_PACKETASKLIST_HH


#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketAskList : public APacket {
        public:
            PacketAskList();
            virtual ~PacketAskList();

        };
    }

}
#endif //CPP_RTYPE_PACKETASKLIST_HH
