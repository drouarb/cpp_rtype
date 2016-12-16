/*
** trouve_b
*/

#include "World.hh"

using namespace client;

World::World()
{
}

World::~World()
{
}

void	World::spawnEntity(ide_t nid, pos_t pos, typeide_t idtype, UIevent_t nevent, tick nturn)
{
  worldEvents.insert(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, pos, idtype, nturn, nevent)));
}

void	World::moveEntity(vec_t vec, pos_t pos, tick nturn, ide_t nid, UIevent_t nevent)
{
  worldEvents.insert(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, vec, pos, nturn, nevent)));
}

void	World::updateEntity(int hp, tick nturn, ide_t nid, UIevent_t nevent)
{
  worldEvents.insert(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, hp, nturn, nevent)));
}

void	World::deleteEntity(ide_t nid, tick nturn, UIevent_t nevent)
{
  worldEvents.insert(std::pair<tick, WorldEvent>(nturn, WorldEvent(nid, nturn, nevent)));
}

tick	World::getTick() const
{
  return (turn);
}

void	World::applyTurn()
{
  std::map<ide_t, Entity*>::iterator it;
  std::map<tick, WorldEvent>::iterator	itEv;
  Entity				*ent;
  pos_t					pos;

  itEv = worldEvents.begin();
  while (itEv->first < turn && itEv != worldEvents.end())
    {
      if (itEv->second.eventtype == SPAWN && (entitys.find(itEv->second.id) == entitys.end()))
	{
	  ent = new Entity(itEv->second.id, itEv->second.type, itEv->second.pos, itEv->first);
	  pos = ent->getPos();
	  entitys.insert(std::pair<ide_t, Entity*>(itEv->second.id, ent));
	}
      else if (itEv->second.eventtype == UPDATE && (entitys.find(itEv->second.id) != entitys.end()))
	{
	  ent = entitys.at(itEv->second.id);
	  pos = ent->getPos();
	  ent->updateEntity(itEv->second.hp);
	}
      else if (itEv->second.eventtype == MOVE && (entitys.find(itEv->second.id) != entitys.end()))
	{
	  ent = entitys.at(itEv->second.id);
	  pos = ent->getPos();
	  ent->moveEntity(itEv->second.vec, itEv->second.pos, itEv->second.turn);
	}
      else if (itEv->second.eventtype == DELETE && (entitys.find(itEv->second.id) != entitys.end()))
	{
	  ent = entitys.at(itEv->second.id);
	  pos = ent->getPos();
	  entitys.erase(itEv->second.id);
	  delete ent;
	}
      UIevents.push_back(std::pair<UIevent_t, pos_t>(itEv->second.UIevent, pos));
      ++itEv;
    }
  it = entitys.begin();
  while (it != entitys.end())
    {
      it->second->applyVec(it->second->getVec(), turn);
      ++it;
    }
}

Entity			*World::getEntityById(ide_t nid)
{
  if (entitys.find(nid) != entitys.end())
    return (entitys.at(nid));
}

std::map<ide_t, Entity*>	World::getEntitys()
{
  return (entitys);
}
