//
// Created by greg on 02/12/2016.
//

#include <entities/EntityAction.hh>

server::EntityAction::EntityAction() : soundToPlay(""), destroy(false), newEntity(nullptr), speedX(0), speedY(0), hp(-1)
{ }

std::ostream &server::operator<<(std::ostream &os, const server::EntityAction &action) {
    os << "soundToPlay: " << action.soundToPlay << " destroy: " << action.destroy << " newEntity: " << action.newEntity;
    return os;
}

