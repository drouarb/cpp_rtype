//
// Created by greg on 17/12/2016.
//

#include <network/packet/PacketSpawnEntity.hh>
#include "events/Spawn.hh"

server::event::Spawn::Spawn(const round_t tick, const entityId_t entityId, pos_t posX, pos_t posY, int hp, const std::string & sprite) :
        AGameEvent(tick, entityId), posX(posX), posY(posY), hp(hp), sprite(sprite) {}

server::event::IGameEvent *server::event::Spawn::getParentEvent() {
    return nullptr;
}

server::entityId_t server::event::Spawn::getEntityId() {
    return this->entityId;
}

server::event::EventType server::event::Spawn::getEventType() {
    return EventType::SPAWN;
}

network::packet::IPacket *server::event::Spawn::createPacket()
{
    auto packet = new network::packet::PacketSpawnEntity();
    packet->setTick(tick);
    packet->setEntityId(entityId);
    packet->setEventId(eventId);
    packet->setHp(hp);
    packet->setSpriteName(sprite);
    packet->setPosX(posX);
    packet->setPosY(posY);
    return (packet);
}

