//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_DESTROY_HH
#define CPP_RTYPE_DESTROY_HH

#include "AGameEvent.hh"

namespace server {
    namespace event {
        class Destroy : public AGameEvent {
        public:
            Destroy(const round_t tick, const entityId_t entityId);

            IGameEvent *getParentEvent() override;

            entityId_t getEntityId() override;

            EventType getEventType() override;

            network::packet::IPacket *createPacket();
        };
    }
}

#endif //CPP_RTYPE_DESTROY_HH
