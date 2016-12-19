//
// Created by lewis_e on 19/12/16.
//

#include "events/Timeline.hh"
#include "Game.hh"

using namespace server;

event::Timeline::Timeline(Game & game) : game(game)
{
    events.reserve(16384);
}

void event::Timeline::addEvent(event::AGameEvent *event)
{
    if (event->getTick() < game.getTick())
    {
        //rewind
    }
    else
    {
        if (event->getTick() >= events.size())
        {
            events.resize(event->getTick() + 1);
        }
        events[event->getTick()].push_back(event);
    }
}
