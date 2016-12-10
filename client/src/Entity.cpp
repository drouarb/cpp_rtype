/*
** trouve_b
*/

#include "Entity.hh"

using namespace client;

Entity::Entity()
{
}

Entity::Entity(ide_t nid, typeide_t nidtype, pos_t npos)
{
  pos = npos;
  posO = npos;
  id = nid;
  idtype = nidtype;
  vec.first = 0;
  vec.second = 0;
  hp = 0;
  lastUpdate = 0;
}

Entity::~Entity()
{
}

pos_t				Entity::getPos() const
{ return pos; }

pos_t				Entity::getOrigin() const
{ return posO; }

vec_t				Entity::getVec() const
{ return vec; }

std::map<tick, vec_t>		Entity::getMove() const
{ return move; }

int				Entity::getHp() const
{ return hp; }

ide_t				Entity::getId() const
{ return id; }

typeide_t			Entity::getTypeid() const
{ return idtype; }

void				Entity::applyVec(vec_t nvec, tick tick)
{
  pos.first += nvec.first;
  pos.second += nvec.second;
  lastUpdate = tick;
}

void				Entity::updateEntity(int nhp)
{
  hp = nhp;
}

void				Entity::moveEntity(vec_t nvec, tick nturn)
{
  move.insert(std::pair<tick, vec_t>(nturn, nvec));
  recalcPos();
}

void				Entity::recalcPos()
{
  std::map<tick, vec_t>::iterator	it;
  std::map<tick, vec_t>::iterator	itnext;

  it = move.begin();
  pos.first = posO.first;
  pos.second = posO.second;
  itnext = it;
  ++itnext;
  while (itnext != move.end())
    {
      pos.first += it->second.first * (itnext->first - it->first);
      pos.second += it->second.second * (itnext->first - it->first);
      ++it;
      ++itnext;
    }
}
