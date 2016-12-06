//
// Created by greg on 02/12/2016.
//

#include "Projectile.hh"

Projectile::Projectile(const server::entityId_t entityId) : IDamager(entityId, "") {}

IDamager::damagePoint_t Projectile::getDamage() {
    return this->damage;
}

void Projectile::collide(server::IEntity *) {

}

server::EntityAction *Projectile::nextAction() {
    return nullptr;
}

ENTRY_POINTS(Projectile);
