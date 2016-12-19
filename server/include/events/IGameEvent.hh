//
// Created by greg on 17/12/2016.
//

#ifndef CPP_RTYPE_IGAMEEVENT_HH
#define CPP_RTYPE_IGAMEEVENT_HH

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
            virtual IGameEvent *getParentEvent()= 0;
            virtual entityId_t getEntityId() = 0;
            virtual EventType getEventType() = 0;
        };
    }
}

#endif //CPP_RTYPE_IGAMEEVENT_HH
