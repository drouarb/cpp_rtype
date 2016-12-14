#include <LibLoader/IDlLoader.hh>
#include <iostream>
#include "Spawn.hh"

using namespace server;

Spawn::Spawn()
{ }

Spawn::Spawn(const Spawn & other) : dlName(other.dlName), time(other.time), posX(other.posX), posY(other.posY)
{ }

Spawn::~Spawn()
{ }

Spawn & Spawn::operator=(const Spawn & other)
{
    dlName = other.dlName;
    time = other.time;
    posX = other.posX;
    posY = other.posY;
    return (*this);
}

Entity * Spawn::trigger(entityId_t id)
{
    Entity * entity = Entity::make(this->dlName, id);
    if (entity == nullptr)
        return (nullptr);
    entity->data.setPosX(this->posX);
    entity->data.setPosY(this->posY);
    return (entity);
}