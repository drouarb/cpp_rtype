/*
** trouve_b
*/

#ifndef MACHINE_HPP_
# define MACHINE_HPP_

#include "SL.hpp"
#include "State.hpp"

namespace FSM
{
  enum Action
    {
      ERROR,
      MA,
    };
  
  template <typename S, typename T>
  class Machine
  {
  private:
    bool		activated;
    S			StateCurrent;
    SL<S, T>		SLFinal;
  public:
    Machine()
    {
      activated = false;
    }

    Machine(SL<S, T> sl)
    {
      SLFinal = sl;
      activated = true;
      StateCurrent = SLFinal.getinitial();
    }
    
    ~Machine()
    {
    }
    
    void		takeSL(SL<S, T> sl)
    {
      activated = true;
      SLFinal = sl;
      StateCurrent = SLFinal.getInitial();
    }
    
    SL<S, T>		simplifySLs(SL<S, T> sl1, SL<S, T> sl2)
    {
      SL<S, T>					slfinal;
      typename std::map<S, State<S, T> >		tmpMap;
      typename std::map<S, State<S, T> >::iterator	it;

      tmpMap = sl1.getStates();
      it = tmpMap.begin();
      while (it != tmpMap.end())
	{
	  State<S, T> newstate;
	  newstate.setNameId(it->second.getNameId());
	  std::map<T, S> nexts;
	  std::map<T, S> itN;
	  nexts = it->second.getNexts();
	  itN = nexts.begin();
	  while (itN != nexts.end())
	    {
	      newstate.addNewNext(itN->second, itN->first);
	      ++itN;
	    }
	  typename std::map<S, State<S, T> >::iterator it2 = sl2.getState(it->first);
	  if (it2 != sl2.nothing())
	    {
	      std::map<T, S> nexts2;
	      std::map<T, S> itN2;
	      nexts2 = it2->second.getNexts();
	      itN2 = nexts2.begin();
	      while (itN2 != nexts2.end())
		{
		  newstate.addNewNext(itN2->second, itN2->first);
		  ++itN2;
		}
	    }
	  slfinal.addNewState(newstate);
	  ++it;
	}
      tmpMap = sl2.getStates();
      it != tmpMap.begin();
      while (it != tmpMap.end())
	{
	  if (slfinal.getState(it->first) == slfinal.nothing())
	    {
	      State<S, T> newstate;
	      newstate.setNameId(it->second.getNameId());
	      std::map<T, S> nexts;
	      std::map<T, S> itN;
	      nexts = it->second.getNexts();
	      itN = nexts.begin();
	      while (itN != nexts.end())
		{
		  newstate.addNewNext(itN->second, itN->first);
		  ++itN;
		}
	      slfinal.addNewState(newstate);
	    }
	  ++it;
	}
      return (slfinal);
    }
    
    Action		takeToken(T token)
    {
      State<S, T>	state;
      
      if (SLFinal.getState(StateCurrent) != SLFinal.nothing())
	{
	  state = getState(StateCurrent)->second;
	  StateCurrent = state.getNextWithToken(token);
	  return (MA);
	}
      return (ERROR);
    }
    
    S			getState() const
    {
      return (StateCurrent);
    }

    void		resetToInitialState()
    {
      if (activated == true)
	StateCurrent = SLFinal.getInitial();
    }
  };
}

#endif /* MACHINE_HPP_ */
