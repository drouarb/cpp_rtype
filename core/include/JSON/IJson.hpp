//
// Json.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:40:28 2016 Esteban Lewis
// Last update Sun May 22 16:00:04 2016 Esteban Lewis
//

#ifndef  IJSONOBJ_HPP_
# define IJSONOBJ_HPP_

# include "JsonParser.hpp"

namespace				JSON
{
  class					IJson
  {
  public:
    virtual ~IJson() { }
    
    virtual std::string const &		Serialize() = 0;
    virtual std::string const &		Serialize(int level) = 0;
    virtual int				ParseFrom(std::string const & text) = 0;
    virtual void			Clear() = 0;
    virtual bool			Newline() const = 0;
    virtual IJson *			Clone() const = 0;
  };
};

# include "JsonObj.hpp"
# include "JsonArr.hpp"
# include "JsonStr.hpp"

#endif
