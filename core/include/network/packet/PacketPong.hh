//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETPONG_HH
#define CPP_RTYPE_PACKETPONG_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketPong : public APacket {
        public:
            PacketPong(const std::string &message = "");

            virtual ~PacketPong();

            const utils::NetworkString &getMessage() const;

            void setMessage(const std::string &msg);

        };
    }

}

#endif //CPP_RTYPE_PACKETPONG_HH
