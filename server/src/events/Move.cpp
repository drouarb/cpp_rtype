//
// Created by greg on 17/12/2016.
//

#include <iostream>
#include <events/Move.hh>
#include <network/packet/PacketMoveEntity.hh>

server::event::Move::Move(const server::round_t tick, const server::entityId_t entityId, const speed_t newVectX,
                          const speed_t newVectY, const pos_t posX, const pos_t posY)
        : AGameEvent(tick, entityId), newVectX(newVectX), newVectY(newVectY), posX(posX), posY(posY) {
}

server::event::IGameEvent *server::event::Move::getParentEvent() {
    return nullptr;
}

server::entityId_t server::event::Move::getEntityId() {
    return this->entityId;
}

server::event::EventType server::event::Move::getEventType() {
    return EventType::MOVE;
}

network::packet::IPacket *server::event::Move::createPacket()
{
    auto packet = new network::packet::PacketMoveEntity();
    packet->setTick(tick);
    packet->setEventId(eventId);
    packet->setEntityId(entityId);
    packet->setPosX(posX * 10.0);
    packet->setPosY(posY * 10.0);
    packet->setVecX(newVectX * 10.0);
    packet->setVecY(newVectY * 10.0);
    return (packet);
}
