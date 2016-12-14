//
// Created by greg on 02/12/2016.
//

#include "EntityInitialization.hh"

server::EntityInitialization::EntityInitialization() : posX(FIELD_BORDER_RIGHT + RIGHT_MARGIN), posY(FIELD_HEIGHT / 2), sprite(""), team(NA), action()
{ }

server::EntityInitialization::EntityInitialization(const std::string &sprite)  : posX(FIELD_BORDER_RIGHT + RIGHT_MARGIN), posY(FIELD_HEIGHT / 2), sprite(sprite), team(NA), action()
{ }
