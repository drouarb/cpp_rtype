#pragma once

#include "Controller.hh"

namespace server {
    class Client {
    private:
        Controller *controller;
        clientId_t clientId;
        std::string name;
    public:
        Client();

        void setName(const std::string &name);

        const std::string &getName() const;

        Client(const Client &toCopy);
        Client &operator=(const Client &toCopy);
        Client(clientId_t clientId);

        Controller *getController() const;

        void setController(Controller *controller);

        clientId_t getClientId() const;


    };

    bool operator==(const Client &lft, const Client &rht);
}