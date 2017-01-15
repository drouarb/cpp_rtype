//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_IGAMEEVENT_HH
#define CPP_RTYPE_IGAMEEVENT_HH

#include <Entity.hh>
#include "Definitions.hh"

namespace server {
    namespace event {

        enum EventType {
            SPAWN,
            MOVE,
            DESTROY,
            MOD_HP
        };

        /**
         * \interface IGameEvent
         * \brief //TODO
         */
        class IGameEvent {
        public:
            virtual const Entity * getEntity() const = 0;
            virtual EventType getEventType() const = 0;
        };
    }
}

#endif //CPP_RTYPE_IGAMEEVENT_HH
