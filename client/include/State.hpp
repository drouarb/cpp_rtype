/*
** trouve_b
*/

#ifndef STATE_HPP_
# define STATE_HPP_

namespace FSM
{
  template <typename S, typename T>
  class State
  {
  private:
    S			nameId;
    std::map<T, S>	nextId;
  public:
    State()
    {
    }
    
    ~State()
    {
    }

    void	setNameId(S nid)
    {
      nameId = nid;
    }

    S		getNameId() const
    {
      return (nameId);
    }

    void	addNewNext(State<S, T> nstate, T tokenNeeded)
    {
      if (nextId.find(tokenNeeded) == nextId.end())
	nextId.insert(std::pair<T, S>(nstate.getNameId, tokenNeeded));
    }

    S		getNextwithToken(T token)
    {
      if (nextId.find(token) != nextId.end())
	{
	  return (nextId.at(token));
	}
      return (nameId);
    }
    
  };
}

#endif /* STATE_HPP_ */
