//
// Created by drouar_b on 11/7/16.
//

#ifndef CPP_BABEL_APACKETLISTENER_HH
#define CPP_BABEL_APACKETLISTENER_HH

#include "network/packet/IPacket.hh"
#include "network/listener/IPacketListener.hh"

namespace network {
    namespace listener {
        class APacketListener : public IPacketListener
        {
        public:
            APacketListener(packet::PacketId id);
            virtual ~APacketListener();

            virtual packet::PacketId getPacketId() const;
            virtual void notify(const packet::IPacket *packet) = 0;

        protected:
            packet::PacketId packetId;
        };
    }
}

#endif //CPP_BABEL_APACKETLISTENER_HH
