//
// Created by greg on 02/12/2016.
//

#include "Projectile.hh"

Projectile::Projectile(const Server::EntityId entityId) : IDamager(entityId, "") {}

IDamager::damagePoint_t Projectile::getDamage() {
    return this->damage;
}

void Projectile::collide(Server::IEntity *) {

}

Server::EntityAction *Projectile::nextAction() {
    return nullptr;
}
