/*
** trouve_b
*/

#ifndef ENTITY_HH_
# define ENTITY_HH_

#include <map>
#include "Definitions.hh"

namespace client
{

  struct moveData
  {
    moveData(pos_t npos, vec_t nvec)
    {pos = npos;vec = nvec;}
    pos_t pos;
    vec_t vec;
  };
  
  class Entity
  {
  private:
    Entity();
  private:
    pos_t			pos;
    pos_t			posO;
    vec_t			vec;
  public:
      void setVec(const vec_t &vec);

  private:
      std::map<tick, moveData>	move;
    int				hp;
    ide_t			id;
    typeide_t			idtype;
    tick			lastUpdate;
  public:
    Entity(ide_t, typeide_t, pos_t, tick);
    ~Entity();
    pos_t			getPos() const;
    pos_t			getOrigin() const;
    vec_t			getVec() const;
    std::map<tick, moveData>	getMove() const;
    int				getHp() const;
    ide_t			getId() const;
    typeide_t			getTypeid() const;
    
    void			applyVec(vec_t, tick);
    void			moveEntity(vec_t, pos_t, tick);
    void			updateEntity(int hp);
    
    void			correctMiddleVec(std::map<tick, moveData>::iterator, vec_t*, pos_t);
    void			correctBeforeVec(std::map<tick, moveData>::iterator, vec_t, pos_t);

  private:
    void			recalcPos();
  };
}

#endif /* ENTITY_HH_ */
