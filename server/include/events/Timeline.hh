//
// Created by lewis_e on 19/12/16.
//

#ifndef CPP_RTYPE_TIMELINE_HH
#define CPP_RTYPE_TIMELINE_HH

#include "AGameEvent.hh"
#include "Definitions.hh"
#include <vector>
#include <list>

namespace server
{
    class Game;

    namespace event
    {
        //stores all events
        //possibility to go back to a past round
        //possibility to go forward a certain number of rounds, sending all event packets
        class Timeline
        {
        public:
            Timeline(Game &);

            void addEvent(AGameEvent * event);

        private:
            Game &game;
            std::vector<std::list<AGameEvent *>> events;
        };
    }
}

#endif //CPP_RTYPE_TIMELINE_HH
