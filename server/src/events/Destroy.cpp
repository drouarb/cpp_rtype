//
// Created by greg on 17/12/2016.
//

#include <network/packet/PacketDeleteEntity.hh>
#include "events/Destroy.hh"

server::event::EventType server::event::Destroy::getEventType() const
{
    return EventType::DESTROY;
}

server::event::Destroy::Destroy(const server::round_t tick, const Entity *entity) : AGameEvent(tick, entity)
{}

network::packet::IPacket *server::event::Destroy::createPacket()
{
    auto packet = new network::packet::PacketDeleteEntity();
    packet->setEntityId(this->entity->data.getId());
    packet->setEventId(this->eventId);
    packet->setTick(this->tick);
    return (packet);
}
