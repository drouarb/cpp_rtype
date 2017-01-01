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
    std::string prefix;
public:
    ConL(std::string prefix): connected(false), prefix(prefix) {}

    virtual void notify(unsigned long fd) {
        std::cout << prefix << "Connected " << fd << std::endl;
        connected = true;
    }

    bool isConnected() const {
        return connected;
    }
};

class DisconL: public listener::ISocketDisconnectionListener {
private:
    bool disconnected;
    std::string prefix;
public:
    DisconL(std::string prefix): disconnected(false), prefix(prefix) {}

    virtual void notify(unsigned long fd) {
        std::cout << prefix << "Disconnected " << fd << std::endl;
        disconnected = true;
    }

    bool isDisconnected() const {
        return disconnected;
    }
};

class DataL: public listener::ISocketDataListener {
private:
    std::vector<uint8_t> data;
    std::string prefix;
public:
    DataL(std::string prefix): prefix(prefix) { };

    virtual void notify(unsigned long fd, const std::vector<unsigned char> &data) {
        std::cout << prefix << "Received " << data.size() << std::endl;
        this->data.insert(this->data.end(), data.begin(), data.end());
    }

    const std::vector<uint8_t> &getData() const {
        return data;
    }
};

int main() {
    ConL *conL = new ConL("[SRV]");
    DataL *dataL = new DataL("[SRV]");
    DisconL *disconL = new DisconL("[SRV]");
    DisconL *cliDisc = new DisconL("[CLI]");
    std::vector<uint8_t> data;
    socket::UnixUDPSocket *server = new socket::UnixUDPSocket(PORT);
    socket::UnixUDPSocket *client = new socket::UnixUDPSocket("127.0.0.1", PORT);

    server->registerConnectionListener(conL);
    server->registerDataListener(dataL);
    server->registerDisconnectionListener(disconL);
    server->run();

    client->registerDisconnectionListener(cliDisc);

    for (uint8_t i = 0; i < 10; i++) {
        data.push_back(i);
    }

    client->run();

    usleep(500000);

    assert(conL->isConnected());

    client->broadcast(data);

    for (int i = 0; i < dataL->getData().size(); i++) {
        assert(data[i] == dataL->getData()[i]);
    }

    client->stop();

    usleep(100000);

    assert(disconL->isDisconnected());

    client->run();

    server->stop();
    usleep(100000);
    assert(cliDisc->isDisconnected());
}
