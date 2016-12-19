#include <Controller.hh>
#include "entities/Player.hh"

void server::Controller::playMove(server::pos_t speedX, server::pos_t speedY) {
    this->player->move(speedX, speedY);
}

void server::Controller::playShoot(server::attackId_t attackId) {
    if (!player)
    {
        return;
    }
    player->shoot(attackId);
}

void server::Controller::setEntity(server::Player *entity) {
    this->player = entity;
}

void server::Controller::destroy() {
}

server::Entity *server::Controller::getEntity() const {
    return entity;
}

void server::Controller::setEntity(server::Entity *entity) {
    Controller::entity = entity;
}

