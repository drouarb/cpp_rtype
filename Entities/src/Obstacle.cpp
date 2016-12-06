//
// Created by greg on 02/12/2016.
//

#include "Obstacle.hh"

Obstacle::Obstacle(const server::entityId_t entityId) : AEntity(entityId, "") {}

void Obstacle::collide(server::IEntity *) {

}

server::EntityAction *Obstacle::nextAction() {
    return nullptr;
}

ENTRY_POINTS(Obstacle);
