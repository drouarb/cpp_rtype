#include <Controller.hh>
#include <Entity.hh>

void server::Controller::playMove(server::pos_t speedX, server::pos_t speedY)
{
    if (!player || !entity || entity->data.getHp() <= 0)
    {
        return;
    }
    this->player->move(speedX, speedY);
}

void server::Controller::playShoot(attackId_t attackId, round_t tick)
{
    if (!player || !entity || entity->data.getHp() <= 0)
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

