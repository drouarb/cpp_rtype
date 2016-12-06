//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETERRORGAME_HH
#define CPP_RTYPE_PACKETERRORGAME_HH

#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketErrorGame : public APacket {
        public:
            PacketErrorGame(const std::string &message = "");

            virtual ~PacketErrorGame();

            const utils::NetworkString &getMessage() const;

            void setMessage(const std::string &msg);

        };
    }

}


#endif //CPP_RTYPE_PACKETERRORGAME_HH
