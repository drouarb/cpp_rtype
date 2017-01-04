//
// Created by greg on 17/12/2016.
//

#include <network/packet/PacketUpdateEntity.hh>
#include "events/ModHP.hh"

server::event::ModHP::ModHP(const server::round_t tick, const Entity *entity, const int hp)
        : AGameEvent(tick, entity), hp(hp)
{}


server::event::EventType server::event::ModHP::getEventType() const
{
    return EventType::MOD_HP;
}

network::packet::IPacket *server::event::ModHP::createPacket()
{
    auto packet = new network::packet::PacketUpdateEntity();
    packet->setTick(tick);
    packet->setEntityId(entity->data.getId());
    packet->setEventId(eventId);
    packet->setHp(static_cast<int16_t>(hp));
    return (packet);
}
