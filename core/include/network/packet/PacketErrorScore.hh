//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETERRORSCORE_HH
#define CPP_RTYPE_PACKETERRORSCORE_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketErrorScore : public APacket {
        public:
            PacketErrorScore(const std::string & message = "");
            virtual ~PacketErrorScore();
            const utils::NetworkString &getMessage() const;
            void setMessage(const std::string &msg);

        };
    }
}


#endif //CPP_RTYPE_PACKETERRORSCORE_HH
