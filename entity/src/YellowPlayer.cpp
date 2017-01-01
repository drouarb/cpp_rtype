//
// Created by greg on 22/12/16.
//

#include "YellowPlayer.hh"

server::EntityInitialization *YellowPlayer::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlB.png";
    return pInitialization;
}

server::ADynamicObject *YellowPlayer::createAttack(server::attackId_t id, server::round_t round) {
    if (id == 1)
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40,
                                this->data->getPosY() + 10,
                                "media/sprites/daggerE.png");
    }
    else
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40,
                                this->data->getPosY() + 10,
                                "media/sprites/daggerE.png");
    }
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new YellowPlayer());
}
}
