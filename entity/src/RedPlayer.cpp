//
// Created by greg on 22/12/16.
//

#include "RedPlayer.hh"

void RedPlayer::shoot(server::round_t current_round) {
    this->attackQueue.push(new MagicMissile(this->data->getPosX() + this->data->getSprite().sizeX,
                                            this->data->getPosY() + this->data->getSprite().sizeY, current_round));
}

server::EntityInitialization *RedPlayer::initialize() {
    server::EntityInitialization *pInitialization = server::Player::initialize();
    pInitialization->sprite.path = "media/sprites/magicalGirlC.png";
    return pInitialization;
}

extern "C"
{
server::ADynamicObject * getInstance()
{
    return (new RedPlayer());
}
}
