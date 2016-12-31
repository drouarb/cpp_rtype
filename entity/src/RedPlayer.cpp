//
// Created by greg on 22/12/16.
//

#include "RedPlayer.hh"

server::EntityInitialization *RedPlayer::initialize(server::round_t r, const server::Grid &e) {
    server::EntityInitialization *pInitialization = server::Player::initialize(r, e);
    pInitialization->sprite.path = "media/sprites/magicalGirlC.png";
    return pInitialization;
}

server::ADynamicObject *RedPlayer::createAttack(server::attackId_t id, server::round_t round)
{
    setAttackWait(id, 5, round);
    return new BasicMissile(this->data->getPosX() + this->data->getSprite().sizeX,
                            this->data->getPosY() + this->data->getSprite().sizeY, "media/sprites/missileC.png");
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new RedPlayer());
}
}
