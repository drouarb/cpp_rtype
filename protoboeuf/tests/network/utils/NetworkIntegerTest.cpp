//
// Created by drouar_b on 10/28/16.
//

#include <stdexcept>
#include <assert.h>
#include <iostream>
#include "network/utils/NetworkInteger.cpp"

using namespace network::utils;

int main() {
    int test = 0;
    t_rawdata data;
    NetworkInteger n(1);
    ssize_t *serialized;
    t_rawdata::iterator it;

    std::cout << "Size tests" << std::endl;
    try {
        NetworkInteger(0);
    } catch(std::length_error e) {
        test = 1;
    }
    assert(test == 1);

    test = 0;
    try {
        NetworkInteger(9);
    } catch(std::length_error e) {
        test = 1;
    }
    assert(test == 1);

    n = NetworkInteger(1);
    assert(n.getSize() == 1);

    std::cout << "Assignement Tests" << std::endl;
    n = NetworkInteger(8, 3);
    assert(n.getValue() == 3);

    n = 42;
    assert(n.getValue() == 42);

    n.setValue(1337);
    assert(n.getValue() == 1337);

    std::cout << "Serialization tests" << std::endl;
    data.resize(0);
    n.setValue(3244);
    n.serialize(&data);
    assert(data.size() == 8);
    serialized = reinterpret_cast<ssize_t *>(&data.front());
    assert(*serialized == 3244);

    data.resize(0);
    data.resize(1);
    n.setValue(3615);
    n.serialize(&data);
    assert(data.size() == 9);
    serialized = reinterpret_cast<ssize_t *>(&data.front() + 1);
    assert(*serialized == 3615);

    std::cout << "Deserialization tests" << std::endl;
    data.resize(0);
    data.resize(3);
    n = NetworkInteger(4);
    test = 0;
    try {
        n.deserialize(&data);
    } catch (std::out_of_range e) {
        test = 1;
    }
    assert(test == 1);

    data.resize(4);
    serialized = reinterpret_cast<ssize_t *>(&data.front());
    *serialized = 1954;
    it = n.deserialize(&data);
    assert(*serialized == n.getValue());
    assert(it == data.end());

    data.resize(0);
    data.resize(8);
    n = NetworkInteger(4);
    serialized = reinterpret_cast<ssize_t *>(&data.front() + 4);
    *serialized = 1914;
    it = n.deserialize(&data, data.begin() + 4);
    assert(n.getValue() == 1914);
    assert(it == data.end());
}
