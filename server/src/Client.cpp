#include <Client.hh>

server::Controller *server::Client::getController() const {
    return controller;
}

void server::Client::setController(server::Controller *controller) {
    Client::controller = controller;
}

server::Client::Client(server::clientId_t clientId) : clientId(clientId) {}
