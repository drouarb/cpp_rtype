#include <Client.hh>

server::Controller *server::Client::getController() const {
    return controller;
}

void server::Client::setController(server::Controller *controller) {
    Client::controller = controller;
}

server::Client::Client(server::clientId_t clientId) : clientId(clientId), controller(nullptr) {}

server::Client::Client() {
    this->clientId = 0;
    this->controller = nullptr;
}

server::Client::Client(const server::Client &toCopy) {
    this->controller = toCopy.controller;
    this->clientId = toCopy.clientId;
}

server::Client &server::Client::operator=(const server::Client &toCopy) {
    this->clientId = toCopy.clientId;
    this->controller = toCopy.controller;
    return *this;
}

server::clientId_t server::Client::getClientId() const {
    return clientId;
}

bool ::server::operator==(const server::Client &lft, const server::Client &rht) {
    return lft.getClientId() == rht.getClientId();
}
