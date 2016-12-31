#include <Controller.hh>
#include "entities/Player.hh"

void server::Controller::playMove(server::pos_t speedX, server::pos_t speedY) {
    this->player->move(speedX * 2, speedY * 2);
}

void server::Controller::playShoot(attackId_t attackId, round_t tick) {
    if (!player)
    {
        return;
    }
    player->shoot(tick, attackId);
}

void server::Controller::setEntity(server::Player *entity) {
    this->player = entity;
}

void server::Controller::destroy() {
    EntityData *data = const_cast<EntityData *>(this->player->data);
    data->setDestroyed(true);
}

server::Entity *server::Controller::getEntity() const {
    return entity;
}

void server::Controller::setEntity(server::Entity *entity) {
    Controller::entity = entity;
}

const server::APlayer *server::Controller::getPlayer() const
{
    return (player);
}

