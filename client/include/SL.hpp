/*
** trouve_b
*/

#ifndef SL_HPP_
# define SL_HPP_

#include "State.hpp"

namespace FSM
{
  template <typename S, typename T>
  class SL
  {
  private:
    typename std::map<S, State<S, T> >	States;
    S					initialState;
  public:
    SL()
    {
    }
    
    ~SL()
    {
    }

    bool		addNewState(State<S, T> nstate)
    {
      if (States.find(nstate.getNameId()) == States.end())
	{
	  States.insert(nstate.getNameId(), nstate);
	  return (true);
	}
      return (false);
    }

    bool					setInitial(S ini)
    {
      if (States.find(ini) != States.end())
	{
	  initialState = ini;
	  return (true);
	}
      return (false);
    }
    
    S						getInitial() const
    {
      return (initialState);
    }
    
    typename std::map<S, State<S, T> >::iterator		getState(S id)
    {
      return (States.find(id));
    }

    typename std::map<S, State<S, T> >::iterator	nothing()
    {
      return (States.end());
    }
  };
}

#endif /* SL_HPP_ */
