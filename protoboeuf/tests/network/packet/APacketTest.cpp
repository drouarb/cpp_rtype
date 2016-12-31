//
// Created by drouar_b on 11/3/16.
//

#include <iostream>
#include <assert.h>
#include "network/utils/NetworkString.cpp"
#include "network/utils/NetworkInteger.cpp"
#include "network/packet/APacket.cpp"

using namespace network::packet;

class PacketTest: public APacket {
public:
    PacketTest():
            APacket(
                    static_cast<PacketId>(0x10),
                    {
                            new network::utils::NetworkInteger(4, 1337),
                            new network::utils::NetworkString("Hello"),
                    }
            )
    { }

    ~PacketTest() { }

    bool check(uint64_t i, std::string str) {
        return (static_cast<network::utils::NetworkInteger *>(schema[0])->getValue() == i &&
                (static_cast<network::utils::NetworkString *>(schema[1]))->compare(str.c_str()) == 0);
    }
};

int main() {
    uint8_t test;
    PacketTest p;
    t_rawdata data;
    uint8_t *packetIdPtr;
    uint32_t *packetSizePtr;
    network::utils::NetworkString  str;
    network::utils::NetworkInteger id(1);
    network::utils::NetworkInteger nb(4);

    std::cout << "Serialization tests" << std::endl;
    p.serialize(&data);
    assert(data.size() - 5 == p.getSize());
    packetIdPtr = &data.front();
    assert(*packetIdPtr == 0x10);
    packetSizePtr = reinterpret_cast<uint32_t *>(&data.front() + 1);
    assert(*packetSizePtr == p.getSize());
    assert(*packetSizePtr == data.size() - 5);

    nb.deserialize(&data, data.begin() + 5);
    assert(nb.getValue() == 1337);

    str.deserialize(&data, data.begin() + 9);
    assert(str.compare("Hello") == 0);

    std::cout << "Deserialization tests" << std::endl;
    data.resize(5);
    packetIdPtr = &data.front();
    *packetIdPtr = 0x10;
    packetSizePtr = reinterpret_cast<uint32_t *>(&data.front() + 1);
    *packetSizePtr = 16 - 5;
    nb.setValue(42);
    nb.serialize(&data);
    str.assign("H3ll0");
    str.serialize(&data);
    p.deserialize(&data);
    assert(p.check(42, "H3ll0"));

    std::cout << "Exception tests" << std::endl;
    test = 0;
    data.resize(0);
    try {
        p.deserialize(&data);
    } catch (std::out_of_range e) {
        test = 1;
    }
    assert(test == 1);

    test = 0;
    data.resize(0);
    id.setValue(0x10);
    id.serialize(&data);
    nb.setValue(PACKET_HEADER_SIZE + 1);
    nb.serialize(&data);
    try {
        p.deserialize(&data);
    } catch (std::out_of_range e) {
        test = 1;
    }
    assert(test == 1);

    test = 0;
    data.resize(0);
    p.serialize(&data);
    data.resize(data.size() - 1);
    try {
        p.deserialize(&data);
    } catch (std::out_of_range e) {
        test = 1;
    }
    assert(test == 1);

    test = 0;
    data.resize(0);
    p.serialize(&data);
    packetIdPtr = &data.front();
    *packetIdPtr = 0x11;
    try {
        p.deserialize(&data);
    } catch (std::domain_error e) {
        test = 1;
    }
    assert(test == 1);
}
