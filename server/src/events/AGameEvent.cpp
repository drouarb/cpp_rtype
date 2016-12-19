//
// Created by greg on 17/12/2016.
//

#include "events/AGameEvent.hh"

server::eventId_t server::event::AGameEvent::lastId = 0;

server::event::AGameEvent::AGameEvent(const server::round_t tick, const server::entityId_t entityId) :
        tick(tick), entityId(entityId)
{
    eventId = lastId;
    ++lastId;
}

std::ostream &server::event::operator<<(std::ostream &os, const AGameEvent &event) {
    os << "tick: " << event.tick << " entityId: " << event.entityId;
    return os;
}

server::round_t server::event::AGameEvent::getTick()
{
    return (tick);
}
