//
// Created by drouar_b on 11/6/16.
//

#ifndef CPP_BABEL_APACKETDATA_HH
#define CPP_BABEL_APACKETDATA_HH

#include "network/utils/NetworkInteger.hh"
#include "IPacket.hh"

namespace network {
    namespace packet {
        class APacketData: public IPacket {
        public:
        protected:
            APacketData(PacketId id, t_rawdata *data = NULL);

        public:
            virtual ~APacketData();

            virtual int getSource() const;
            virtual void setSource(int src);
            virtual uint16_t getSize() const;
            virtual PacketId getPacketId() const;
            virtual void serialize(t_rawdata *data) const;
            virtual t_rawdata::iterator deserialize(t_rawdata *data);
            virtual t_rawdata::iterator deserialize(t_rawdata *data, t_rawdata::iterator it);

            void setData(t_rawdata *data);
            const t_rawdata& getData() const;

        protected:
            int src;
            t_rawdata data;
            const utils::NetworkInteger packetId;
        };
    }
}


#endif //CPP_BABEL_PACKETAUDIO_HH
