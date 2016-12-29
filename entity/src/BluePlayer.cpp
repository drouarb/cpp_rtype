//
// Created by greg on 22/12/16.
//

#include "BluePlayer.hh"

void BluePlayer::shoot(server::round_t round) {
    server::Player::shoot(round);
}

server::EntityInitialization *BluePlayer::initialize(server::round_t round, const std::vector<server::Entity *> &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlA.png";
    return pInitialization;
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new BluePlayer());
}
}
