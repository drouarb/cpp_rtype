//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_SPAWN_HH
#define CPP_RTYPE_SPAWN_HH

#include <ostream>
#include "AGameEvent.hh"

namespace server {
    namespace event {

        class Spawn : public AGameEvent {

            const pos_t posX;
            const pos_t posY;
            const int hp;
            const std::string sprite;

        public:
            Spawn(const round_t tick, const entityId_t entityId, pos_t posX, pos_t posY, int hp, const std::string & sprite);

            IGameEvent *getParentEvent() override;

            entityId_t getEntityId() override;

            EventType getEventType() override;

            network::packet::IPacket *createPacket();
        };


    }
}


#endif //CPP_RTYPE_SPAWN_HH
