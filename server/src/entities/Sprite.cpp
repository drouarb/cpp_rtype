//
// Created by lewis_e on 15/12/16.
//

#include "Sprite.hh"

using namespace server;

Sprite::Sprite() : path(""), sizeX(0), sizeY(0)
{ }

Sprite::Sprite(const std::string &path) : path(path)
{
    //TODO: read file to know size
    sizeX = 0;
    sizeY = 0;
}

Sprite::Sprite(const Sprite &other) : path(other.path), sizeX(other.sizeX), sizeY(other.sizeY)
{ }

Sprite::~Sprite()
{ }

Sprite & Sprite::operator=(const Sprite &other)
{
    path = other.path;
    sizeX = other.sizeX;
    sizeY = other.sizeY;
    return (*this);
}

bool Sprite::operator==(const Sprite &other)
{
    return (path == other.path);
}