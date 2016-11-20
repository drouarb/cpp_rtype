//
// Created by drouar_b on 11/2/16.
//

#ifndef CPP_BABEL_APACKET_HH
#define CPP_BABEL_APACKET_HH

#include "network/utils/NetworkInteger.hh"
#include "network/utils/NetworkString.hh"
#include "network/packet/IPacket.hh"

namespace network {
    namespace packet {
        class APacket: public IPacket {
        protected:
            APacket(PacketId id, std::vector<utils::INetworkUtil *> schema);

        public:
            virtual ~APacket();

            virtual int getSource() const;
            virtual void setSource(int src);
            virtual PacketId getPacketId() const;
            virtual uint16_t getSize() const;
            virtual void serialize(t_rawdata *data) const;
            virtual t_rawdata::iterator deserialize(t_rawdata *data);
            virtual t_rawdata::iterator deserialize(t_rawdata *data, t_rawdata::iterator it);

        protected:
            int src;
            const utils::NetworkInteger packetId;
            const std::vector<utils::INetworkUtil *> schema;
        };
    }
}

#endif //CPP_BABEL_APACKET_HH
