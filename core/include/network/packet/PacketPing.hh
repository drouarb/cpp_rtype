//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETPING_HH
#define CPP_RTYPE_PACKETPING_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketPing : public APacket {
        public:
            PacketPing(const std::string &message = "");

            virtual ~PacketPing();

            const utils::NetworkString &getMessage() const;

            void setMessage(const std::string &msg);


        };
    }

}


#endif //CPP_RTYPE_PACKETPING_HH
