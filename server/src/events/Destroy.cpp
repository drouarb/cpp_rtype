//
// Created by greg on 17/12/2016.
//

#include <network/packet/PacketDeleteEntity.hh>
#include "events/Destroy.hh"

server::event::IGameEvent *server::event::Destroy::getParentEvent() {
    return nullptr;
}

server::entityId_t server::event::Destroy::getEntityId() {
    return this->entityId;
}

server::event::EventType server::event::Destroy::getEventType() {
    return EventType::DESTROY;
}

server::event::Destroy::Destroy(const server::round_t tick, const server::entityId_t entityId) : AGameEvent(tick,
                                                                                                            entityId) {}

network::packet::IPacket *server::event::Destroy::createPacket()
{
    auto packet = new network::packet::PacketDeleteEntity();
    packet->setEntityId(this->entityId);
    packet->setEventId(this->eventId);
    packet->setTick(this->tick);
    return (packet);
}
