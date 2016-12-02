//
// Created by greg on 02/12/2016.
//

#include "EntityAction.hh"

Server::EntityAction::EntityAction() : soundToPlay(""), destroy(false), newEntity(nullptr) {}

std::ostream &Server::operator<<(std::ostream &os, const Server::EntityAction &action) {
    os << "soundToPlay: " << action.soundToPlay << " destroy: " << action.destroy << " newEntity: " << action.newEntity;
    return os;
}

