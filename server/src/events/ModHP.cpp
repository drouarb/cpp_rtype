//
// Created by greg on 17/12/2016.
//

#include <network/packet/PacketUpdateEntity.hh>
#include "events/ModHP.hh"

server::event::ModHP::ModHP(const server::round_t tick, const server::entityId_t entityId, const int hp)
        : AGameEvent(tick,
                     entityId), hp(hp) {}

server::event::IGameEvent *server::event::ModHP::getParentEvent() {
    return nullptr;
}

server::entityId_t server::event::ModHP::getEntityId() {
    return this->entityId;
}

server::event::EventType server::event::ModHP::getEventType() {
    return EventType::MOD_HP;
}

network::packet::IPacket *server::event::ModHP::createPacket()
{
    auto packet = new network::packet::PacketUpdateEntity();
    packet->setTick(tick);
    packet->setEntityId(entityId);
    packet->setEventId(eventId);
    packet->setHp(hp);
    return (packet);
}
