//
// Created by drouar_b on 12/13/16.
//

#include "network/listener/PacketFactoryDataListener.hh"

network::listener::PacketFactoryDataListener::PacketFactoryDataListener(const network::PacketFactory &pf): pf(pf) {
}

void network::listener::PacketFactoryDataListener::notify(unsigned long fd, const std::vector<uint8_t> &data) {
    pf.dataCallback(fd, data);
}
