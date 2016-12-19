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
        //send cancels for every packet
        //undo spawns and destroys
        //once at the sought round, find latest update and move for every entity (or spawn if none)
        //tick until the right round

        //TODO: if a received player control packet is too old, ignore it
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
