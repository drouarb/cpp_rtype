#include <Client.hh>

server::Controller *server::Client::getController() const {
    return controller;
}

void server::Client::setController(server::Controller *controller) {
    Client::controller = controller;
}

server::Client::Client(server::clientId_t clientId) : clientId(clientId), controller(nullptr) {}

server::Client::Client() {
    this->name = "";
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

void server::Client::setName(const std::string &name) {
    this->name = name;
}

const std::string &server::Client::getName() const {
    return name;
}

bool ::server::operator==(const server::Client &lft, const server::Client &rht) {
    return lft.getClientId() == rht.getClientId();
}
