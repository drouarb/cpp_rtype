//
// Created by greg on 22/12/16.
//

#include <iostream>
#include "BluePlayer.hh"

server::EntityInitialization *BluePlayer::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlC.png";
    return pInitialization;
}

server::ADynamicObject *BluePlayer::createAttack(server::attackId_t id, server::round_t round) {
    if (id == 1)
    {
        setAttackWait(id, 3, round);
        return new MagicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX + BULLET_SIZE + 1,
                                this->data->getPosY(),
                                round, "media/sprites/magicBulletBlue.png");
    }
    else
    {
        setAttackWait(id, BASIC_MISSILE_TIME, round);
        return new BasicMissile(this, this->data->getPosX() + this->data->getSprite().sizeX - 40,
                                this->data->getPosY() + 10,
                                "media/sprites/daggerB.png");
    }
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new BluePlayer());
}
}
