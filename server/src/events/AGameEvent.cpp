//
// Created by greg on 17/12/2016.
//

#include "events/AGameEvent.hh"
#include "Entity.hh"

server::eventId_t server::event::AGameEvent::lastId = 0;

server::event::AGameEvent::AGameEvent(const server::round_t tick, const Entity *entity) :
        tick(tick), entity(entity)
{
    eventId = lastId;
    ++lastId;
}

const server::Entity * server::event::AGameEvent::getEntity() const
{
    return (entity);
}

std::ostream &server::event::operator<<(std::ostream &os, const AGameEvent &event) {
    os << "tick: " << event.tick << " entityId: " << event.entity->data.getId();
    return os;
}

server::round_t server::event::AGameEvent::getTick()
{
    return (tick);
}