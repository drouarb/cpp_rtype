//
// Created by lewis_e on 08/12/16.
//

#include "BasicEntity.hh"

ENTRY_POINT(BasicEntity)

BasicEntity::BasicEntity() : id(0), team(server::NA), sprite(""), posX(FIELD_BORDER_RIGHT + RIGHT_MARGIN), posY(FIELD_HEIGHT / 2), speedX(0), speedY(0), hp(-1), destroyed(false)
{ }

void BasicEntity::setEntityId(server::entityId_t id)
{
    this->id = id;
}

server::entityId_t BasicEntity::getEntityId()
{
    return id;
}

server::Team BasicEntity::getTeam()
{
    return team;
}

std::string &BasicEntity::getSprite()
{
    return sprite;
}

void BasicEntity::setPosX(server::pos_t pos)
{
    this->posX = pos;
}

void BasicEntity::setPosY(server::pos_t pos)
{
    this->posY = pos;
}

server::pos_t BasicEntity::getPosX()
{
    return posX;
}

server::pos_t BasicEntity::getPosY()
{
    return posY;
}

void BasicEntity::setSpeedX(server::speed_t sp)
{
    this->speedX = sp;
}

server::speed_t BasicEntity::getSpeedX()
{
    return speedX;
}

void BasicEntity::setSpeedY(server::speed_t sp)
{
    this->speedY = sp;
}

server::speed_t BasicEntity::getSpeedY()
{
    return this->speedY;
}

void BasicEntity::modHp(int m)
{
    this->hp += m;
}

int BasicEntity::getHp()
{
    return (hp);
}

void BasicEntity::destroy()
{
    this->destroyed = true;
}

void BasicEntity::restore()
{
    this->destroyed = false;
}

bool BasicEntity::isDestroyed()
{
    return destroyed;
}

void BasicEntity::collide(server::IEntity *)
{

}

server::EntityAction *BasicEntity::nextAction()
{
    this->speedX--;
    return (new server::EntityAction());
}
