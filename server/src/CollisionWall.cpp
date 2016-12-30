//
// Created by lewis_e on 28/12/16.
//

#include "CollisionWall.hh"

server::CollisionWall::CollisionWall() : x_pos(false), x_neg(false), y_pos(false), y_neg(false)
{ }

server::CollisionWall::CollisionWall(const server::CollisionWall &other) : x_pos(other.x_pos), x_neg(other.x_neg), y_pos(other.y_pos), y_neg(other.y_neg)
{ }

server::CollisionWall::~CollisionWall()
{ }

server::CollisionWall &server::CollisionWall::operator=(const server::CollisionWall &other)
{
    x_pos = other.x_pos;
    x_neg = other.x_neg;
    y_pos = other.y_pos;
    y_neg = other.y_neg;
    return (*this);
}

void server::CollisionWall::add(server::Axis axis, server::Direction dir)
{
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

