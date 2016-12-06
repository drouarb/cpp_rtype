//
// Created by greg on 02/12/2016.
//

#include "PowerUp.hh"

PowerUp::PowerUp(const server::entityId_t entityId) : AEntity(entityId, "") {}

void PowerUp::collide(server::IEntity *) {

}

server::EntityAction *PowerUp::nextAction() {
    return nullptr;
}

ENTRY_POINTS(PowerUp);