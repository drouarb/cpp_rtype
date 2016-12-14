//
// Json.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:40:28 2016 Esteban Lewis
// Last update Sun May 22 17:58:58 2016 Esteban Lewis
//

#ifndef  JSONOBJ_HPP_
# define JSONOBJ_HPP_

# include <map>
# include <string>
# include <stdexcept>
# include "IJson.hpp"

namespace				JSON
{
  class					JsonObj : public IJson, private JsonParser
  {
  public:
    JsonObj();
    JsonObj(JsonObj const &);
    ~JsonObj();
      
    void				AddObj(std::string const & key,
					       IJson const & val);
    IJson const &			GetObj(std::string const & key) const;
    IJson &				GetObj(std::string const & key);
    std::map<std::string, IJson *> const & GetMap() const;
    std::string const &			Serialize();
    std::string const &			Serialize(int level);
    int					ParseFrom(std::string const & text);
    void				Clear();
    bool				Newline() const;
    IJson *				Clone() const;

  private:
    std::map<std::string, IJson *>	objs;
    std::string				serialized;
  };
};

#endif
