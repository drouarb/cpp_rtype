//
// Created by lewis_e on 13/12/16.
//

#include <helpers/libloader/getDlLoader.hpp>
#include <iostream>
#include <entities/Entity.hh>

using namespace server;

Entity::Entity() : obj(nullptr), data()
{ }

Entity::Entity(ADynamicObject *obj, entityId_t id, round_t round, const std::vector<Entity *> &entities) : Entity()
{
    initialize(obj, id, round, entities);
}

Entity::~Entity()
{
    if (obj)
        delete obj;
}

void Entity::initialize(ADynamicObject *obj, entityId_t id, round_t round, const std::vector<Entity *> &entities)
{
    this->obj = obj;
    this->obj->data = &data;
    data.initialize(this->obj->initialize(round, entities), id);
}

Entity * Entity::make(const std::string &path, entityId_t id, round_t round, const std::vector<Entity *> &entities)
{
    try
    {
        auto * obj = getDlLoader<ADynamicObject>(path)->getInstance();
        return (new Entity(obj, id, round, entities));
    }
    catch (std::runtime_error &e)
    {
        std::cerr << "Entity creation error: " << e.what() << std::endl;
        return (nullptr);
    }
}