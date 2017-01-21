//
// Created by greg on 17/12/2016.
//

#include <network/packet/PacketSpawnEntity.hh>
#include "events/Spawn.hh"

server::event::Spawn::Spawn(const round_t tick, const Entity * entity, pos_t posX, pos_t posY, int hp, const std::string & sprite) :
        AGameEvent(tick, entity), posX(posX), posY(posY), hp(hp), sprite(sprite)
{
    lastId++; //inc another time for simulation
}

server::event::EventType server::event::Spawn::getEventType() const
{
    return EventType::SPAWN;
}

network::packet::IPacket *server::event::Spawn::createPacket()
{
    auto packet = new network::packet::PacketSpawnEntity();
    packet->setTick(tick);
    packet->setEntityId(entity->data.getId());
    packet->setEventId(eventId);
    packet->setHp(hp);
    packet->setSpriteName(sprite);
    packet->setPosX(posX * 100.0);
    packet->setPosY(posY * 100.0);
    return (packet);
}

