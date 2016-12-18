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
            ERROR_HANDSHAKE         = 0x00,
            SYN                     = 0x01,
            SYN_ACK                 = 0x02,
            ACK                     = 0x03,
            REGISTER                = 0x04,
            DISCONNECT              = 0x05,
            PING                    = 0x06,
            PONG                    = 0x07,

            ERROR_LIST              = 0x10,
            ASK_LIST                = 0x11,
            GAME_LIST               = 0x12,

            ERROR_GAME              = 0x20,
            JOIN                    = 0x21,
            QUIT                    = 0x22,
            GAME_DATA               = 0x23,

            EVENT_ERROR             = 0x30,
            CANCEL_EVENT            = 0x31,
            PLAYER_MOVE             = 0x32,
            PLAYER_ATTACK           = 0x33,
            SPAWN_ENTITY            = 0x34,
            DELETE_ENTITY           = 0x35,
            UPDATE_ENTITY           = 0x36,
            MOVE_ENTITY             = 0x37,
            PLAY_SOUND              = 0x38,

            ERROR_SCORE             = 0x60,
            ASK_LEADERBOARD         = 0x61,
            LEADER_BOARD            = 0x62

        };


        class IPacket {
        public:
            virtual ~IPacket() {};

            virtual unsigned long getSource() const = 0;
            virtual void setSource(unsigned long src) = 0;
            virtual uint16_t getSize() const = 0;
            virtual PacketId getPacketId() const = 0;
            virtual void serialize(t_rawdata *data) const = 0;
            virtual t_rawdata::iterator deserialize(t_rawdata *data) = 0;
            virtual t_rawdata::iterator deserialize(t_rawdata *data, t_rawdata::iterator it) = 0;
        };
    }
}

#endif //CPP_BABEL_IPACKET_HH
