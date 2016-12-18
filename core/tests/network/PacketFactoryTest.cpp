//
// Created by drouar_b on 12/17/16.
//

#include <network/PacketFactory.hh>
#include <network/packet/PacketQuit.hh>
#include <network/listener/ListenerTemplate.hpp>
#include <iostream>
#include <unistd.h>
#include <assert.h>

using namespace network;

class testListener: public network::ListenerTemplate<network::packet::PacketQuit, network::packet::QUIT> {
public:
    testListener(): APacketListener(packet::QUIT), received(false) { }

    virtual void notify(const packet::PacketQuit *packet) {
        std::cout << "Received packet" << std::endl;
        received = true;
    }

    bool isReceived() const {
        return received;
    }

private:
    bool received;
};

int main() {
    PacketFactory server(52349);
    PacketFactory client("127.0.0.1", 52349);
    packet::PacketQuit packetQuit;
    testListener *clientListener = new testListener;
    testListener *serverListener = new testListener;

    server.registerListener(serverListener);
    client.registerListener(clientListener);

    server.run();
    client.run();

    sleep(1);
    client.broadcast(packetQuit);
    sleep(1);
    assert(serverListener->isReceived() == true);

    server.broadcast(packetQuit);
    sleep(1);
    assert(clientListener->isReceived() == true);
}