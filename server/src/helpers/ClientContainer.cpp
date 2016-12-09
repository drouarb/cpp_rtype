//
// Created by greg on 08/12/2016.
//

#include "helpers/ClientContainer.hh"
#include <algorithm>

server::Client &server::ClientContainer::get(int id) {
    try {
        return (*this).at(id);
    } catch (std::out_of_range &e) {
        (*this)[id] = Client(id);//TODO see this with Esteban
        this->clientList.push_back((*this)[id]);
    }
    return get(id);
}

server::Client &server::ClientContainer::operator[](int id) {
    return this->get(id);
}

void server::ClientContainer::remove(int id) {
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
