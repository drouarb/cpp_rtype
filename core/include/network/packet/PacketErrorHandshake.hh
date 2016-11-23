//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETERRORHANDSHAKE_HH
#define CPP_RTYPE_PACKETERRORHANDSHAKE_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketErrorHandshake : public APacket {
        public:
            PacketErrorHandshake(const std::string &message = "");

            virtual ~PacketErrorHandshake();

            const utils::NetworkString &getMessage() const;

            void setMessage(const std::string &msg);


        };
    }

}

#endif //CPP_RTYPE_PACKETERRORHANDSHAKE_HH
