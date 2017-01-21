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
            ModHP(const server::round_t tick, const Entity *entity, const int hp);

            EventType getEventType() const override;

            network::packet::IPacket *createPacket();
        };
    }
}

#endif //CPP_RTYPE_MODHP_HH
