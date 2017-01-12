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
            Destroy(const round_t tick, const Entity *entity);

            EventType getEventType() const override;

            network::packet::IPacket *createPacket();
        };
    }
}

#endif //CPP_RTYPE_DESTROY_HH
