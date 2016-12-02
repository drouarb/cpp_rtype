//
// Created by greg on 02/12/2016.
//

#include "PowerUp.hh"

PowerUp::PowerUp(const Server::EntityId entityId) : AEntity(entityId, "") {}

void PowerUp::collide(Server::IEntity *) {

}

Server::EntityAction *PowerUp::nextAction() {
    return nullptr;
}
