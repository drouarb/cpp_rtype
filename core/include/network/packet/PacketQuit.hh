//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETQUIT_HH
#define CPP_RTYPE_PACKETQUIT_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketQuit  : public APacket{
        public:
            PacketQuit();
            virtual ~PacketQuit();
        };
    }
}


#endif //CPP_RTYPE_PACKETQUIT_HH