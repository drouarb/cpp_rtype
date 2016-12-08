#pragma once

#include "Controller.hh"

namespace server {
    class Client {
    private:
        Controller *controller;
        const clientId_t clientId;
    public:
        Client(clientId_t clientId);

        Controller *getController() const;

        void setController(Controller *controller);
    };
}