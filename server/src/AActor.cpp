//
// Created by greg on 02/12/2016.
//

#include "AActor.hh"

using namespace Server;

AActor::AActor(const Server::EntityId entityId, const std::string &sprite) : AEntity(entityId, sprite) {}

void AActor::hit(int damage) {
    this->hp -= damage;
    if (this->hp <= 0) {
        this->destroyed = true;
    }
}
