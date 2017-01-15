//
// Created by lewis_e on 13/12/16.
//

#include <helpers/libloader/getDlLoader.hpp>
#include <iostream>
#include <entities/Entity.hh>

using namespace server;

Entity::Entity() : obj(nullptr), data()
{ }

Entity::Entity(ADynamicObject *obj, entityId_t id, round_t round, const Grid &environment) : Entity()
{
    initialize(obj, id, round, environment);
}

Entity::~Entity()
{
    if (obj)
        delete obj;
}

void Entity::initialize(ADynamicObject *obj, entityId_t id, round_t round, const Grid &environment)
{
    this->obj = obj;
    this->obj->data = &data;
    data.initialize(this->obj->initialize(round, environment), id);
}

Entity * Entity::make(const std::string &path, entityId_t id, round_t round, const Grid &environment)
{
    try
    {
        auto * obj = getDlLoader<ADynamicObject>(path)->getInstance();
        return (new Entity(obj, id, round, environment));
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Entity creation error: " << e.what() << std::endl;
        return (nullptr);
    }
}