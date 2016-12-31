//
// Created by lewis_e on 28/12/16.
//

#include <Entity.hh>
#include <iostream>
#include "CollisionWall.hh"
#include "EntityAction.hh"

server::CollisionWall::CollisionWall() : x_pos(false), x_neg(false), y_pos(false), y_neg(false), is_set(false), collisions(0)
{ }

server::CollisionWall::CollisionWall(const server::CollisionWall &other) : x_pos(other.x_pos), x_neg(other.x_neg), y_pos(other.y_pos), y_neg(other.y_neg), is_set(other.is_set), collisions(other.collisions)
{ }

server::CollisionWall::~CollisionWall()
{ }

server::CollisionWall &server::CollisionWall::operator=(const server::CollisionWall &other)
{
    x_pos = other.x_pos;
    x_neg = other.x_neg;
    y_pos = other.y_pos;
    y_neg = other.y_neg;
    is_set = other.is_set;
    collisions = other.collisions;
    return (*this);
}

void server::CollisionWall::add(server::Axis axis, server::Direction dir, const Entity * entity)
{
    is_set = true;
    if (axis == X)
    {
        if (dir == POS)
        {
            x_pos = true;
        }
        else
        {
            x_neg = true;
        }
    }
    else
    {
        if (dir == POS)
        {
            y_pos = true;
        }
        else
        {
            y_neg = true;
        }
    }
    collisions.push_back(entity);
}

void server::CollisionWall::apply(server::EntityAction *action)
{
    if (x_pos && action->speedX > 0)
        action->speedX = 0;
    if (x_neg && action->speedX < 0)
        action->speedX = 0;
    if (y_pos && action->speedY > 0)
        action->speedY = 0;
    if (y_neg && action->speedY < 0)
        action->speedY = 0;
}

bool server::CollisionWall::isSet() const
{
    return (is_set);
}

void server::CollisionWall::reset()
{
    this->operator=(CollisionWall());
}

bool server::CollisionWall::includes(const Entity *entity) const
{
    for (auto it : collisions)
    {
        if (it == entity)
            return (true);
    }
    return (false);
}



