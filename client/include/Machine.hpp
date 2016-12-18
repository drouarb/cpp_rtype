/*
** trouve_b
*/

#ifndef MACHINE_HPP_
# define MACHINE_HPP_

#include "SL.hpp"

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
      SL<S, T>		slfinal;
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
