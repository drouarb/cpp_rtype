//
// Created by greg on 17/12/2016.
//

#include "events/Spawn.hh"

server::event::Spawn::Spawn(const round_t tick, const entityId_t entityId, pos_t posX, pos_t posY) : AGameEvent(tick,
                                                                                                                entityId), posX(posX), posY(posY) {}

server::event::IGameEvent *server::event::Spawn::getParentEvent() {
    return nullptr;
}

server::entityId_t server::event::Spawn::getEntityId() {
    return this->entityId;
}

server::event::EventType server::event::Spawn::getEventType() {
    return EventType::SPAWN;
}
