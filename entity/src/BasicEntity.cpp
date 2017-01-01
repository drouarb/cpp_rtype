//
// Created by lewis_e on 08/12/16.
//

#include <iostream>
#include <entities/Entity.hh>
#include <IDamager.hh>
#include "BasicEntity.hh"
#include "../../server/include/Grid.hh"

using namespace server;


BasicEntity::BasicEntity() : destroyed(false)
{ }


void BasicEntity::collide(const server::Entity &entity, server::round_t current_round)
{
    this->destroyed = true;
}

EntityAction *BasicEntity::act(round_t current_round, const server::Grid &)
{
    EntityAction * a = new EntityAction();
    if (this->destroyed) {
        a->hp = 0;
        a->destroy = true;
        return a;
    }
    a->speedX = this->data->getVectX() + 1;
    return (a);
}

EntityInitialization * BasicEntity::initialize(round_t, const Grid &environment)
{
    EntityInitialization *initialization = new EntityInitialization();
    initialization->action.hp = 100;
    return initialization;
}

hp_t BasicEntity::getDamage() {
    return 0;
}

Tribool BasicEntity::collidesWith(const Entity &entity) {
    return (this->data->getTeam() != entity.data.getTeam() ? T_TRUE : T_FALSE);
}

extern "C"
{
EXPORT_SYM ADynamicObject * getInstance()
{
    return (new BasicEntity());
}
}
