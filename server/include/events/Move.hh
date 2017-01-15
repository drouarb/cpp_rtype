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
            Move(const server::round_t tick, const server::Entity * entity, const speed_t newVectX,
                             const speed_t newVectY, const pos_t posX, const pos_t posY);

            EventType getEventType() const override;

            network::packet::IPacket *createPacket();

        };
    }
}

#endif //CPP_RTYPE_MOVE_HH
