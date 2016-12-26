/*
** trouve_b
*/

#include <vector>
#include <map>
#include <list>
#include "Definitions.hh"
#include "Entity.hh"
#include "GameUIInterface.hh"

#ifndef WORLD_HH_
# define WORLD_HH_

#include <iostream>

#define RESERVE_UIEVENTS 10

namespace client
{

  class WorldEvent
  {
  public:
    WorldEvent(ide_t nid, pos_t npos, typeide_t nidtype, tick nturn, UIevent_t nevent)
    {//std::cout<<"WOWlespawn"<<std::endl;
       id=nid;pos=npos;type=nidtype;UIevent=nevent;turn=nturn;eventtype=worldEventType::SPAWN;}
    
    WorldEvent(ide_t nid, int nhp, tick nturn, UIevent_t nevent)
    {//std::cout<<"WOWleupdate"<<std::endl;
      id=nid;hp=nhp;UIevent=nevent;turn=nturn;eventtype=worldEventType::UPDATE;}
    
    WorldEvent(ide_t nid, vec_t nvec, pos_t npos, tick nturn, UIevent_t nevent)
    {//std::cout<<"WOWlemove"<<std::endl;
      id=nid;vec=nvec;pos=npos;UIevent=nevent;turn=nturn;eventtype=worldEventType::MOVE;}
    
    WorldEvent(ide_t nid, tick nturn, UIevent_t nevent)
    {//std::cout<<"WOWledelete"<<std::endl;
      id=nid;UIevent=nevent;turn=nturn;eventtype=worldEventType::DELETE;}
    
    worldEventType	eventtype;
    tick		turn;
    ide_t		id;
    pos_t		pos;
    vec_t		vec;
    int			hp;
    typeide_t		type;
    UIevent_t		UIevent;
  };
  
  class World
  {
  private:
      std::mutex *world_mut;
    tick					turn;	
    std::map<ide_t, Entity*>			entitys;
    std::vector<std::pair<UIevent_t, pos_t> >	UIevents;
    std::list<std::pair<tick, WorldEvent> >			worldEvents;
      GameUIInterface *gameui;
  public:
    World(std::mutex *mmut, GameUIInterface *ngameui);
    ~World();
    void					spawnEntity(ide_t, pos_t, typeide_t, UIevent_t, tick);
    void					moveEntity(vec_t, pos_t, tick, ide_t, UIevent_t);
    void					updateEntity(int hp, tick, ide_t, UIevent_t);
    void					deleteEntity(ide_t, tick, UIevent_t);
    Entity					*getEntityById(ide_t nid);
    std::map<ide_t, Entity*>			getEntitys();
    void					applyTurn();
    tick					getTick() const;
    std::vector<std::pair<UIevent_t, pos_t> >	getEvents();
  };
}

#endif /* WORLD_HH_ */
