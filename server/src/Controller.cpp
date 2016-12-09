#include <Controller.hh>
#include <iostream>

void server::Controller::playMove(server::pos_t speedX, server::pos_t speedY) {
    this->entity->setSpeedX(speedX);
    this->entity->setSpeedY(speedY);
}

void server::Controller::playShoot(server::attackId_t attackId) {
    std::cout << "<Piou Piou Piou> will be execute next turn" << std::endl;
    this->getPlayer()->shoot(attackId);
}

void server::Controller::setEntity(server::IEntity *entity) {
    this->entity = entity;
}

server::IPlayer *server::Controller::getPlayer() {
    return static_cast<IPlayer *>(this->entity);
}
