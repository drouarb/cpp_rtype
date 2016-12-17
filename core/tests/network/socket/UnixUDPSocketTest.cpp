//
// Created by drouar_b on 12/9/16.
//

#include <iostream>
#include <network/listener/ISocketConnectionListener.hh>
#include <network/socket/UnixUDPSocket.hh>
#include <unistd.h>
#include <assert.h>

#define PORT 48762

using namespace network;

class ConL: public listener::ISocketConnectionListener {
private:
    bool connected;
public:
    ConL(): connected(false) {}

    virtual void notify(unsigned long fd) {
        std::cout << "Connected " << fd << std::endl;
        connected = true;
    }

    bool isConnected() const {
        return connected;
    }
};

class DisconL: public listener::ISocketDisconnectionListener {
private:
    bool disconnected;
public:
    DisconL(): disconnected(false) {}

    virtual void notify(unsigned long fd) {
        std::cout << "Disconnected " << fd << std::endl;
        disconnected = true;
    }

    bool isDisconnected() const {
        return disconnected;
    }
};

class DataL: public listener::ISocketDataListener {
    std::vector<uint8_t> data;
public:
    virtual void notify(unsigned long fd, const std::vector<unsigned char> &data) {
        std::cout << "Received " << data.size() << std::endl;
        this->data.insert(this->data.end(), data.begin(), data.end());
    }

    const std::vector<uint8_t> &getData() const {
        return data;
    }
};

int main() {
    ConL *conL = new ConL;
    DataL *dataL = new DataL;
    std::vector<uint8_t> data;
    DisconL *disconL = new DisconL;
    socket::UnixUDPSocket *server = new socket::UnixUDPSocket(PORT);
    socket::UnixUDPSocket *client = new socket::UnixUDPSocket("127.0.0.1", PORT);

    server->run();
    server->registerConnectionListener(conL);
    server->registerDataListener(dataL);
    server->registerDisconnectionListener(disconL);

    for (uint8_t i = 0; i < 10; i++) {
        data.push_back(i);
    }

    client->run();

    usleep(500000);

    assert(conL->isConnected());

    usleep(500000);

    client->broadcast(data);

    for (int i = 0; i < dataL->getData().size(); i++) {
        assert(data[i] == dataL->getData()[i]);
    }

    client->stop();

    sleep(7);

    assert(disconL->isDisconnected());
}