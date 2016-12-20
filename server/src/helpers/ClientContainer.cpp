//
// Created by greg on 08/12/2016.
//

#include "helpers/ClientContainer.hh"
#include <algorithm>
#include <iostream>

server::Client &server::ClientContainer::get(clientId_t id) {
    try {
        return (*this).at(id);
    } catch (std::out_of_range &e) {
        throw std::logic_error("Unknow client with id " + std::to_string(id) + " try to action but was not connected");
    }
}

void server::ClientContainer::remove(clientId_t id) {
    try {
        Client &client = (*this).at(id);
        this->clientList.erase(std::find(this->clientList.begin(), this->clientList.end(), client));
        this->erase(id);
    } catch (std::out_of_range &e) {
    }
}

const std::list<server::Client> &server::ClientContainer::toStdList() const {
    return this->clientList;
}

server::Client &server::ClientContainer::create(unsigned long id) {
    (*this)[id] = Client(id);
    this->clientList.push_back((*this)[id]);
    INFO("Create client for " << id)
    return (*this)[id];
}