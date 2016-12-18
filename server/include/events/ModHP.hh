//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_MODHP_HH
#define CPP_RTYPE_MODHP_HH

#include "AGameEvent.hh"

namespace server {
    namespace event {
        class ModHP : public AGameEvent {
        private:
            const int hp;
        public:
            ModHP(const server::round_t tick, const server::entityId_t entityId, const int hp);

            IGameEvent *getParentEvent() override;

            entityId_t getEntityId() override;

            EventType getEventType() override;

            network::packet::IPacket *createPacket();
        };
    }
}

#endif //CPP_RTYPE_MODHP_HH
