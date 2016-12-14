#include <Controller.hh>
#include "Player.hh"

void server::Controller::playMove(server::pos_t speedX, server::pos_t speedY) {
    if (!this->entity) {
        throw std::logic_error("Entity was not set");
    }
    this->entity->setSpeedX(speedX);
    this->entity->setSpeedY(speedY);
}

void server::Controller::playShoot(server::attackId_t attackId) {
    if (!entity)
    {
        return;
    }
    entity->shoot(attackId);
}

void server::Controller::setEntity(server::Player *entity) {
    this->entity = entity;
}

void server::Controller::destroy() {

}
