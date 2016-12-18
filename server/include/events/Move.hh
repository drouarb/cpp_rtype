//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_MOVE_HH
#define CPP_RTYPE_MOVE_HH

#include <ostream>
#include "AGameEvent.hh"

namespace server {
    namespace event {

        class Move : public AGameEvent {
        private:
            const speed_t newVectX;
            const speed_t newVectY;
            const pos_t posX;
            const pos_t posY;

        public:
            Move(const server::round_t tick, const server::entityId_t entityId, const speed_t newVectX,
                             const speed_t newVectY, const pos_t posX, const pos_t posY);

            IGameEvent *getParentEvent() override;

            entityId_t getEntityId() override;

            EventType getEventType() override;

            network::packet::IPacket *createPacket();

        };
    }
}

#endif //CPP_RTYPE_MOVE_HH
