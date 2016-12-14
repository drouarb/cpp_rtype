//
// Created by lewis_e on 08/12/16.
//

#include <iostream>
#include "BasicEntity.hh"

using namespace server;

extern "C"
{
    ADynamicObject * getInstance()
    {
        return (new BasicEntity());
    }
}

BasicEntity::BasicEntity()
{ }

void BasicEntity::collide(Entity *)
{ }

EntityAction *BasicEntity::nextAction()
{
    EntityAction * a = new EntityAction();
    a->speedX = this->data->getVectX() + 1;
    return (a);
}

EntityInitialization * BasicEntity::initialize()
{
    return (new EntityInitialization());
}