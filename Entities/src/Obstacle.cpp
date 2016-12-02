//
// Created by greg on 02/12/2016.
//

#include "ObstacleTest.hh"

Obstacle::Obstacle(const Server::EntityId entityId) : AEntity(entityId, "") {}

void Obstacle::collide(Server::IEntity *) {

}

Server::EntityAction *Obstacle::nextAction() {
    return nullptr;
}
