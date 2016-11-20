//
// Created by drouar_b on 11/3/16.
//

#include <assert.h>
#include "network/utils/NetworkString.cpp"
#include "network/utils/NetworkInteger.cpp"
#include "network/packet/APacketData.cpp"

using namespace network::packet;

class PacketTest : public APacketData {
public:
    PacketTest() : APacketData(AUDIO, NULL) {}

    ~PacketTest() {}
};

int main() {
    uint8_t test;
    PacketTest p;
    t_rawdata data;
    t_rawdata serializedData;
    uint8_t *packetIdPtr;
    uint32_t *packetSizePtr;
    network::utils::NetworkInteger id(1, AUDIO);
    network::utils::NetworkInteger size(4);

    std::cout << "Serialization tests" << std::endl;
    data.resize(3, 2);
    p.setData(&data);
    p.serialize(&serializedData);
    assert(serializedData.size() - 5 == p.getSize());
    packetIdPtr = &serializedData.front();
    assert(*packetIdPtr == AUDIO);
    packetSizePtr = reinterpret_cast<uint32_t *>(&serializedData.front() + 1);
    assert(*packetSizePtr == p.getSize());
    assert(*packetSizePtr == serializedData.size() - PACKET_HEADER_SIZE);
    assert(memcmp(&data.front(), &serializedData.front() + 5, 3) == 0);

    std::cout << "Deserialization tests" << std::endl;
    serializedData.resize(0);
    size.setValue(5);
    id.serialize(&serializedData);
    size.serialize(&serializedData);
    data.resize(0);
    data.resize(5, 5);
    serializedData.insert(serializedData.end(), data.begin(), data.end());
    p.deserialize(&serializedData);
    assert(p.getPacketId() == AUDIO);
    assert(size.getValue() == serializedData.size() - PACKET_HEADER_SIZE);
    assert(p.getSize() == serializedData.size() - PACKET_HEADER_SIZE);
    assert(memcmp(&p.getData().front(), &serializedData.front() + 5, 5) == 0);

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
    id.setValue(AUDIO);
    id.serialize(&data);
    size.setValue(PACKET_HEADER_SIZE + 1);
    size.serialize(&data);
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
    *packetIdPtr = ERROR_CALL;
    try {
        p.deserialize(&data);
    } catch (std::domain_error e) {
        test = 1;
    }
    assert(test == 1);
}