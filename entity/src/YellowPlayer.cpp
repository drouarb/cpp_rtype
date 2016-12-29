//
// Created by greg on 22/12/16.
//

#include "YellowPlayer.hh"

void YellowPlayer::shoot(server::round_t attackId) {
    server::Player::shoot(attackId);
}

server::EntityInitialization *YellowPlayer::initialize(server::round_t round, const std::vector<server::Entity *> &entity) {
    server::EntityInitialization *pInitialization = server::Player::initialize(round, entity);
    pInitialization->sprite.path = "media/sprites/magicalGirlD.png";
    return pInitialization;
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new YellowPlayer());
}
}
