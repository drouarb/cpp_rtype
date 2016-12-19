//
// Created by lewis_e on 13/12/16.
//

#include "Entity.hh"
#include <helpers/libloader/getDlLoader.hpp>
#include <iostream>

using namespace server;

Entity::Entity() : obj(nullptr), data()
{ }

Entity::Entity(ADynamicObject *obj, entityId_t id) : Entity()
{
    initialize(obj, id);
}

Entity::~Entity()
{
    if (obj)
        delete obj;
}

void Entity::initialize(ADynamicObject *obj, entityId_t id)
{
    this->obj = obj;
    this->obj->data = &data;
    data.initialize(this->obj->initialize(), id);
}

Entity * Entity::make(const std::string & path, entityId_t id)
{
    try
    {
        auto * obj = getDlLoader<ADynamicObject>(path)->getInstance();
        return (new Entity(obj, id));
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Entity creation error: " << e.what() << std::endl;
        return (nullptr);
    }
}