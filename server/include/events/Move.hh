//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_MOVE_HH
#define CPP_RTYPE_MOVE_HH

#include "AGameEvent.hh"

namespace server {
    namespace event {

        class Move : public AGameEvent {
        private:
            const int posX;
            const int posY;
            const int newVectX;
            const int newVectY;

        public:
            Move(const server::round_t tick, const server::entityId_t entityId, const int newVectX,
                             const int newVectY, const int posX, const int posY);

            IGameEvent *getParentEvent() override;

            entityId_t getEntityId() override;

            EventType getEventType() override;
        };

    }
}

#endif //CPP_RTYPE_MOVE_HH
