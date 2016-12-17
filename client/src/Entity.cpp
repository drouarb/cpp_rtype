/*
** trouve_b
*/

#include <iostream>
#include "Entity.hh"

using namespace client;

Entity::Entity()
{
}

Entity::Entity(ide_t nid, typeide_t nidtype, pos_t npos, tick nturn)
{
  pos = npos;
  posO = npos;
  id = nid;
  idtype = nidtype;
  vec = vec_t(0, 0);
  move.insert(std::pair<tick, moveData>(nturn, moveData(npos, vec_t(0, 0))));
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

std::map<tick, moveData>	Entity::getMove() const
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
  vec = nvec;
  lastUpdate = tick;
}

void				Entity::updateEntity(int nhp)
{
  hp = nhp;
}

void				Entity::moveEntity(vec_t nvec, pos_t npos, tick nturn)
{
  std::map<tick, moveData>::iterator it;

  if ((it = move.find(nturn)) != move.end())
    {
      std::cerr << "readaptation de move sur tick identique à faire" << std::endl;
      return;
    }
  it = move.begin();
  while (it != move.end() && it->first > nturn)
    ++it;
  if (it == move.end() || it->first < nturn)
    {
      if (it == move.end())
	{
	  --it;
	  correctBeforeVec(it, nvec, npos);
	  vec = nvec;
	  pos = npos;
	  lastUpdate = nturn;
	}
      else
	correctMiddleVec(it, &nvec, npos);
      if (it->second.vec != nvec)
	move.insert(std::pair<tick, moveData>(nturn, moveData(npos, nvec)));
      recalcPos();
    }
}

void			Entity::correctMiddleVec(std::map<tick, moveData>::iterator itO, vec_t *nvec, pos_t npos)
{
  std::map<tick, moveData>::iterator itA;
  
  itO->second.vec.first = npos.first - itO->second.pos.first;
  itO->second.vec.second = npos.second - itO->second.pos.second;
  itA = itO;
  ++itA;
  nvec->first = itA->second.pos.first - npos.first;
  nvec->second = itA->second.pos.second - npos.second;
}

void			Entity::correctBeforeVec(std::map<tick, moveData>::iterator itO, vec_t nvec, pos_t npos)
{
  itO->second.vec.first = npos.first - itO->second.pos.first;
  itO->second.vec.second = npos.second - itO->second.pos.second;
}

void				Entity::recalcPos()
{
  std::map<tick, moveData>::iterator	it;
  std::map<tick, moveData>::iterator	itnext;

  it = move.begin();
  pos.first = posO.first;
  pos.second = posO.second;
  itnext = it;
  ++itnext;
  while (itnext != move.end())
    {
      pos.first += it->second.vec.first * (itnext->first - it->first);
      pos.second += it->second.vec.second * (itnext->first - it->first);
      ++it;
      ++itnext;
    }
}
