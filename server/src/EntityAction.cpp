//
// Created by greg on 02/12/2016.
//

#include "EntityAction.hh"

server::EntityAction::EntityAction() : soundToPlay(""), destroy(false), newEntity(nullptr) {}

std::ostream &server::operator<<(std::ostream &os, const server::EntityAction &action) {
    os << "soundToPlay: " << action.soundToPlay << " destroy: " << action.destroy << " newEntity: " << action.newEntity;
    return os;
}

