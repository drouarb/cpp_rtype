//
// Created by drouar_b on 11/2/16.
//

#ifndef CPP_BABEL_IPACKET_HH
#define CPP_BABEL_IPACKET_HH

#include "network/utils/INetworkUtil.hh"

#define PROTOCOL_VERSION     7

#define PACKET_ID_SIZE       1
#define PACKET_SIZE_SIZE     4
#define PACKET_HEADER_SIZE   (PACKET_ID_SIZE + PACKET_SIZE_SIZE)

namespace network {
    namespace packet {

        enum PacketId {
            ERROR_CONNECT  = 0x00,
            WELCOME_SERVER = 0x01,
            CONNECT        = 0x02,
            DISCONNECT     = 0x03,
            ACCEPT         = 0x04,

            ERROR_SIGN     = 0x10,
            LOGIN          = 0x11,
            REGISTER       = 0x12,

            ERROR_CONTACT  = 0x20,
            CONTACTS_LIST  = 0x21,
            CONTACT_ADD    = 0x22,
            CONTACT_REMOVE = 0x23,

            ERROR_CALL     = 0x30,
            CALL           = 0x31,
            NOTIFY_CALL    = 0x32,
            CANCEL         = 0x33,
            REJECT         = 0x34,

            ERROR_CLIENT   = 0x80,
            WELCOME_CLIENT = 0x81,
            ANSWER         = 0x82,
            HANG_UP        = 0x83,

            ERROR_DATA     = 0x90,
            AUDIO          = 0x91,
        };

        class IPacket {
        public:
            virtual ~IPacket() {};

            virtual int getSource() const = 0;
            virtual void setSource(int src) = 0;
            virtual uint16_t getSize() const = 0;
            virtual PacketId getPacketId() const = 0;
            virtual void serialize(t_rawdata *data) const = 0;
            virtual t_rawdata::iterator deserialize(t_rawdata *data) = 0;
            virtual t_rawdata::iterator deserialize(t_rawdata *data, t_rawdata::iterator it) = 0;
        };
    }
}

#endif //CPP_BABEL_IPACKET_HH
