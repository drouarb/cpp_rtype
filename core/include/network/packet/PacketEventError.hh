//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETEVENTERROR_HH
#define CPP_RTYPE_PACKETEVENTERROR_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketEventError : public APacket {
        public:
            PacketEventError(const std::string &message = "");

            virtual ~PacketEventError();

            const utils::NetworkString &getMessage() const;

            void setMessage(const std::string &msg);

        };
    }

}


#endif //CPP_RTYPE_PACKETEVENTERROR_HH
