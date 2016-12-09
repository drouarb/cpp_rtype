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

int main() {
    ConL *conL = new ConL;
    DisconL *disconL = new DisconL;
    socket::UnixUDPSocket *server = new socket::UnixUDPSocket(PORT);
    socket::UnixUDPSocket *client = new socket::UnixUDPSocket("127.0.0.1", PORT);

    server->run();
    server->registerConnectionListener(conL);
    server->registerDisconnectionListener(disconL);

    client->run();

    usleep(500000);

    assert(conL->isConnected());

    usleep(500000);

    client->stop();

    sleep(6);

    assert(disconL->isDisconnected());
}