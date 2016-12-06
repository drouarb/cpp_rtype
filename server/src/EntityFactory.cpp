#include "IEntity.hh"
#include "LibLoader/getDlLoader.hpp"

using namespace server;

IEntity * IEntity::make(const std::string & path)
{
    try
    {
        return (getDlLoader<IEntity>(path)->getInstance());
    }
    catch (std::runtime_error)
    {
        return (nullptr);
    }
}