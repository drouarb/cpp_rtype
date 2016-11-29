//
// Created by drouar_b on 11/7/16.
//

#ifndef CPP_RTYPE_IPACKETLISTENER_HH
#define CPP_RTYPE_IPACKETLISTENER_HH

#include <network/packet/IPacket.hh>

namespace network {
    namespace listener {
        class IPacketListener {
        public:
            virtual ~IPacketListener() { }

            virtual packet::PacketId getPacketId() const = 0;
            virtual void notify(const packet::IPacket *packet) = 0;
        };
    }
}

#endif //CPP_RTYPE_IPACKETLISTENER_HH
