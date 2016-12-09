#include <Controller.hh>

void server::Controller::playMove(server::pos_t speedX, server::pos_t speedY) {
    this->entity->setSpeedX(speedX);
    this->entity->setSpeedY(speedY);
}

void server::Controller::playShoot(server::attackId_t attackId) {
    this->getPlayer()->shoot(attackId);
}

void server::Controller::setEntity(server::IEntity *entity) {
    this->entity = entity;
}

server::IPlayer *server::Controller::getPlayer() {
    return reinterpret_cast<IPlayer *>(this->entity);
}

void server::Controller::destroy()
{

}
