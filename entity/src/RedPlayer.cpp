//
// Created by greg on 22/12/16.
//

#include "RedPlayer.hh"

server::EntityInitialization *RedPlayer::initialize(server::round_t r, const server::Grid &e) {
    server::EntityInitialization *pInitialization = server::Player::initialize(r, e);
    pInitialization->sprite.path = "media/sprites/magicalGirlA.png";
    return pInitialization;
}

server::ADynamicObject *RedPlayer::createAttack(server::attackId_t id, server::round_t round)
{
    if (id == 0)
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40, this->data->getPosY() + 10,
                                "media/sprites/daggerA.png");
    }
    else
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40, this->data->getPosY() + 10,
                                "media/sprites/daggerA.png");
    }
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new RedPlayer());
}
}
