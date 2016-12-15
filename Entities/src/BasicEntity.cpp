//
// Created by lewis_e on 08/12/16.
//

#include <iostream>
#include <entities/Entity.hh>
#include <IDamager.hh>
#include "BasicEntity.hh"

using namespace server;

extern "C"
{
    ADynamicObject * getInstance()
    {
        return (new BasicEntity());
    }
}

BasicEntity::BasicEntity() : destroyed(false)
{ }


void BasicEntity::collide(const Entity &)
{
    this->destroyed = true;
}

EntityAction *BasicEntity::nextAction()
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

EntityInitialization * BasicEntity::initialize()
{
    EntityInitialization *initialization = new EntityInitialization();
    initialization->action.hp = 100;
    return initialization;
}

damage_t BasicEntity::getDamage() {
    return 0;
}
