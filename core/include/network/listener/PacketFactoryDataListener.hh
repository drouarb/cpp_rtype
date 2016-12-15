//
// Created by drouar_b on 12/13/16.
//

#ifndef CPP_RTYPE_PACKETFACTORYDATALISTENER_HH
#define CPP_RTYPE_PACKETFACTORYDATALISTENER_HH

#include <network/PacketFactory.hh>
#include "ISocketDataListener.hh"

namespace network {
    namespace listener {
        class PacketFactoryDataListener: public ISocketDataListener {
        public:
            PacketFactoryDataListener(const PacketFactory &pf);

            virtual void notify(unsigned long fd, const std::vector<uint8_t> &data);

        private:
            const PacketFactory &pf;
        };
    }
}

#endif //CPP_RTYPE_PACKETFACTORYDATALISTENER_HH
