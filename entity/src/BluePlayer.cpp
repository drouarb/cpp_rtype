//
// Created by greg on 22/12/16.
//

#include "BluePlayer.hh"

server::EntityInitialization *BluePlayer::initialize(server::round_t round, const server::Grid &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlB.png";
    return pInitialization;
}

server::ADynamicObject *BluePlayer::createAttack(server::attackId_t id, server::round_t round) {
//    return Player::createAttack(id, round);
    setAttackWait(id, 5, round);
    return new BasicMissile(this->data->getPosX() + this->data->getSprite().sizeX,
                            this->data->getPosY() + this->data->getSprite().sizeY, "media/sprites/missileB.png");
//    return server::Player::createAttack(id, round);
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new BluePlayer());
}
}
