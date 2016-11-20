//
// Created by drouar_b on 10/28/16.
//

#include <stdexcept>
#include <assert.h>
#include <iostream>
#include "network/utils/NetworkString.cpp"

using namespace network::utils;

int main()
{
    int test;
    t_rawdata data;
    uint16_t *strsize;
    NetworkString n("");
    t_rawdata::iterator it;

    std::cout << "Size tests" << std::endl;
    n = "Hello";
    assert(n.getSize() == 7);

    std::cout << "Serialization tests" << std::endl;
    data.resize(0);
    n = "Kekulus Maximus";
    n.serialize(&data);
    assert(data.size() == 17);
    assert(data.size() == n.getSize());
    strsize = reinterpret_cast<uint16_t *>(&data.front());
    assert(*strsize == 15);
    assert(strcmp(n.c_str(), reinterpret_cast<char *>(&data.front() + 2)) == 0);

    data.resize(0);
    data.resize(4);
    n = "Kekulus Maximus";
    n.serialize(&data);
    assert(data.size() == 21);
    assert(data.size() == n.getSize() + 4);
    strsize = reinterpret_cast<uint16_t *>(&data.front() + 4);
    assert(*strsize == 15);
    assert(strcmp(n.c_str(), reinterpret_cast<char *>(&data.front() + 6)) == 0);

    std::cout << "Deserialisation tests" << std::endl;
    test = 0;
    data.resize(1);
    try {
        n.deserialize(&data);
    } catch (std::out_of_range e) {
        test = 1;
    }
    assert(test == 1);

    test = 0;
    data.resize(3);
    strsize = reinterpret_cast<uint16_t *>(&data.front());
    *strsize = 2;
    try {
        n.deserialize(&data);
    } catch (std::out_of_range e) {
        test = 1;
    }
    assert(test == 1);

    test = 0;
    data.resize(3);
    strsize = reinterpret_cast<uint16_t *>(&data.front());
    *strsize = 1;
    try {
        n.deserialize(&data);
    } catch (std::out_of_range e) {
        test = 1;
    }
    assert(test == 0);

    test = 0;
    data.resize(2);
    strsize = reinterpret_cast<uint16_t *>(&data.front());
    *strsize = 0;
    try {
        n.deserialize(&data);
    } catch (std::out_of_range e) {
        test = 1;
    }
    assert(test == 0);

    data.resize(5);
    strsize = reinterpret_cast<uint16_t *>(&data.front());
    *strsize = 3;
    strcpy(reinterpret_cast<char *>(&data.front() + 2), "KeK");
    it = n.deserialize(&data);
    assert(n == "KeK");
    assert(it == data.end());

    data.resize(10);
    strsize = reinterpret_cast<uint16_t *>(&data.front() + 5);
    *strsize = 3;
    strcpy(reinterpret_cast<char *>(&data.front() + 7), "KWA");
    it = n.deserialize(&data, data.begin() + 5);
    assert(n == "KWA");
    assert(it == data.end());
}