//
// Created by lewis_e on 12/12/16.
//

#include "entities/EntityData.hh"
#include "cstring"

using namespace server;

EntityData::EntityData()
{}

EntityData::~EntityData()
{ }

void EntityData::initialize(EntityInitialization * ei, entityId_t id)
{
    this->team = ei->team;
    this->sprite = ei->sprite;
    this->posX = ei->posX;
    this->posY = ei->posY;
    this->vectX = ei->action.speedX;
    this->vectY = ei->action.speedY;
    this->destroyed = false;
    this->hp = ei->action.hp;
    this->id = id;
}

Team EntityData::getTeam() const
{
    return team;
}

void EntityData::setTeam(Team team)
{
    EntityData::team = team;
}

const Sprite &EntityData::getSprite() const
{
    return sprite;
}

void EntityData::setSprite(const Sprite &sprite)
{
    EntityData::sprite = sprite;
}

entityId_t EntityData::getId() const
{
    return id;
}

void EntityData::setId(entityId_t id)
{
    EntityData::id = id;
}

pos_t EntityData::getPosX() const
{
    return posX;
}

void EntityData::setPosX(pos_t posX)
{
    EntityData::posX = posX;
}

pos_t EntityData::getPosY() const
{
    return posY;
}

void EntityData::setPosY(pos_t posY)
{
    EntityData::posY = posY;
}

speed_t EntityData::getVectX() const
{
    return vectX;
}

void EntityData::setVectX(speed_t vectX)
{
    EntityData::vectX = vectX;
}

speed_t EntityData::getVectY() const
{
    return vectY;
}

void EntityData::setVectY(speed_t vectY)
{
    EntityData::vectY = vectY;
}

hp_t EntityData::getHp() const
{
    return hp;
}

void EntityData::setHp(int hp)
{
    EntityData::hp = hp;
}

bool EntityData::isDestroyed() const
{
    return destroyed;
}

void EntityData::setDestroyed(bool destroyed)
{
    this->destroyed = destroyed;
}
