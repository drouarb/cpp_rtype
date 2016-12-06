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

IEntity * Spawn::trigger()
{
    IEntity * entity = IEntity::make(this->dlName);
    if (entity == nullptr)
        return (nullptr);
    entity->setPosX(this->posX);
    entity->setPosY(this->posY);
    return (entity);
}