//
// Created by greg on 17/12/2016.
//

#include "events/ModHP.hh"

server::event::ModHP::ModHP(const server::round_t tick, const server::entityId_t entityId, const int diff)
        : AGameEvent(tick,
                     entityId), diff(diff) {}

server::event::IGameEvent *server::event::ModHP::getParentEvent() {
    return nullptr;
}

server::entityId_t server::event::ModHP::getEntityId() {
    return this->entityId;
}

server::event::EventType server::event::ModHP::getEventType() {
    return EventType::MOD_HP;
}
