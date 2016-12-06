//
// Created by greg on 02/12/2016.
//

#include "BasicEntity.hh"

BasicEntity::BasicEntity(const server::entityId_t entityId) : AEntity(entityId, "") {}

void BasicEntity::collide(server::IEntity *) {

}

server::EntityAction *BasicEntity::nextAction() {
    return nullptr;
}

ENTRY_POINTS(BasicEntity);

