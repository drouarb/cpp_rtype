//
// Created by greg on 01/01/17.
//

#include <entities/Entity.hh>
#include "entities/VisualFx.hh"

extern "C"
{
EXPORT_SYM server::ADynamicObject * getInstance()
{
    return (new server::VisualFx::PowerUp());
}
}
