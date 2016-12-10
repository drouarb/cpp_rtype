/*
** trouve_b
*/

#ifndef ENTITY_HH_
# define ENTITY_HH_

#include <map>
#include "Definitions.hh"

namespace client
{

  class Entity
  {
  private:
    Entity();
  private:
    pos_t			pos;
    pos_t			posO;
    vec_t			vec;
    std::map<tick, vec_t>	move;
    int				hp;
    ide_t			id;
    typeide_t			idtype;
    tick			lastUpdate;
  public:
    Entity(ide_t, typeide_t, pos_t);
    ~Entity();
    pos_t			getPos() const;
    pos_t			getOrigin() const;
    vec_t			getVec() const;
    std::map<tick, vec_t>	getMove() const;
    int				getHp() const;
    ide_t			getId() const;
    typeide_t			getTypeid() const;

    /*
    ** return true when the entity is dead false
    ** when the entity is already alive
    */
    
    void			applyVec(vec_t, tick);
    void			moveEntity(vec_t, tick);
    void			updateEntity(int hp);

  private:
    void			recalcPos();
  };
}

#endif /* ENTITY_HH_ */
