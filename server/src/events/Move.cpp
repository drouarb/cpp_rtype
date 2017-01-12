//
// Created by greg on 17/12/2016.
//

#include <iostream>
#include <events/Move.hh>
#include <network/packet/PacketMoveEntity.hh>

server::event::Move::Move(const server::round_t tick, const server::Entity * entity, const speed_t newVectX,
                          const speed_t newVectY, const pos_t posX, const pos_t posY)
        : AGameEvent(tick, entity), newVectX(newVectX), newVectY(newVectY), posX(posX), posY(posY) {
}

server::event::EventType server::event::Move::getEventType() const
{
    return EventType::MOVE;
}

network::packet::IPacket *server::event::Move::createPacket()
{
    auto packet = new network::packet::PacketMoveEntity();
    packet->setTick(tick);
    packet->setEventId(eventId);
    /*<<<<<<< HEAD
    packet->setEntityId(entityId);
    packet->setPosX(posX * 10.0);
    packet->setPosY(posY * 10.0);
    packet->setVecX(newVectX * 10.0);
    packet->setVecY(newVectY * 10.0);
    =======*/
    packet->setEntityId(entity->data.getId());
    packet->setPosX(posX * 10.0);
    packet->setPosY(posY * 10.0);
    packet->setVecX(newVectX * 10.0);
    packet->setVecY(newVectY * 10.0);
    //>>>>>>> 8a774d96ae6a09a4e00ed39258ae6ac90700ee68
    return (packet);
}
