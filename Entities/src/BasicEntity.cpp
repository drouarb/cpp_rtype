//
// Created by greg on 02/12/2016.
//

#include "BasicEntity.hh"

BasicEntity::BasicEntity(const Server::EntityId entityId) : AEntity(entityId, "") {}

void BasicEntity::collide(Server::IEntity *) {

}

Server::EntityAction *BasicEntity::nextAction() {
    return nullptr;
}

ENTRY_POINTS(BasicEntity);

