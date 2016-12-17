//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_AGAMEEVENT_HH
#define CPP_RTYPE_AGAMEEVENT_HH

#include <network/packet/IPacket.hh>
#include <ostream>
#include "IGameEvent.hh"

namespace server {
    namespace event {
        class AGameEvent : public IGameEvent {
        protected:
            const round_t tick;
            const entityId_t entityId;

        public:
            AGameEvent(const round_t tick, const entityId_t entityId);
            network::packet::IPacket *createPacket();

            friend std::ostream &operator<<(std::ostream &os, const AGameEvent &event);
        };
        std::ostream &operator<<(std::ostream &os, const AGameEvent &event);


    }
}

#endif //CPP_RTYPE_AGAMEEVENT_HH
