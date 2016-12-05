//
// Created by celeriy on 23/11/16.
//

#ifndef CPP_RTYPE_PACKETERRORLIST_HH
#define CPP_RTYPE_PACKETERRORLIST_HH


#include <network/packet/APacket.hh>

namespace network {
    namespace packet {
        class PacketErrorList : public APacket {
        public:
            PacketErrorList(const std::string &message = "");

            virtual ~PacketErrorList();

            const utils::NetworkString &getMessage() const;

            void setMessage(const std::string &msg);

        };
    }

}

#endif //CPP_RTYPE_PACKETERRORLIST_HH
