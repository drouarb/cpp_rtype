//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_SPAWN_HH
#define CPP_RTYPE_SPAWN_HH

#include "AGameEvent.hh"

namespace server {
    namespace event {

        class Spawn : public AGameEvent {

            const int posX;
            const int posY;

        public:
            Spawn(const round_t tick, const entityId_t entityId, pos_t posX, pos_t posY);

            IGameEvent *getParentEvent() override;

            entityId_t getEntityId() override;

            EventType getEventType() override;
        };

    }
}


#endif //CPP_RTYPE_SPAWN_HH
