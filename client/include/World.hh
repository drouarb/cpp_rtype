/*
** trouve_b
*/

#include <vector>
#include <map>
#include <list>
#include "Definitions.hh"
#include "Entity.hh"

#ifndef WORLD_HH_
# define WORLD_HH_

namespace client
{

  struct WorldEvent
  {
    WorldEvent(ide_t nid, pos_t npos, typeide_t nidtype, tick nturn, UIevent_t nevent)
    {id=nid;pos=npos;type=nidtype;UIevent=nevent;turn=nturn;eventtype=SPAWN;}
    
    WorldEvent(ide_t nid, int nhp, tick nturn, UIevent_t nevent)
    {id=nid;hp=nhp;UIevent=nevent;turn=nturn;eventtype=UPDATE;}
    
    WorldEvent(ide_t nid, vec_t nvec, tick nturn, UIevent_t nevent)
    {id=nid;vec=nvec,UIevent=nevent;turn=nturn;eventtype=MOVE;}
    
    WorldEvent(ide_t nid, tick nturn, UIevent_t nevent)
    {id=nid;UIevent=nevent;turn=nturn;eventtype=DELETE;}
    
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
    tick					turn;	
    std::map<ide_t, Entity*>			entitys;
    std::vector<std::pair<UIevent_t, pos_t> >	UIevents;
    std::map<tick, WorldEvent>			worldEvents;
  public:
    World();
    ~World();
    void			spawnEntity(ide_t, pos_t, typeide_t, UIevent_t, tick);
    void			moveEntity(vec_t, tick, ide_t, UIevent_t);
    void			updateEntity(int hp, tick, ide_t, UIevent_t);
    void			deleteEntity(ide_t, tick, UIevent_t);
    Entity			*getEntityById(ide_t nid);
    std::map<ide_t, Entity*>	getEntitys();
    void			applyTurn();
    tick			getTick() const;
  };
}

#endif /* WORLD_HH_ */
