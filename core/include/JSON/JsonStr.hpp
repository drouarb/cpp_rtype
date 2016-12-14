//
// Json.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:40:28 2016 Esteban Lewis
// Last update Sun May 22 15:58:33 2016 Esteban Lewis
//

#ifndef  JSONSTR_HPP_
# define JSONSTR_HPP_

# include <string>
# include "IJson.hpp"

namespace				JSON
{
  class					JsonStr : public IJson, private JsonParser
  {
  public:
    JsonStr();
    JsonStr(std::string const &);
    ~JsonStr();
      
    void				Set(std::string const & newval);
    std::string const &			Get() const;
    std::string const &			Serialize();
    std::string const &			Serialize(int level);
    int					ParseFrom(std::string const & text);
    void				Clear();
    bool				Newline() const;
    IJson *				Clone() const;
      
  private:
    std::string				val;
    std::string				serialized;
  };
};

#endif
