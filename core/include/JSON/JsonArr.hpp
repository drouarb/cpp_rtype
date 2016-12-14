//
// Json.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:40:28 2016 Esteban Lewis
// Last update Sun May 22 15:57:10 2016 Esteban Lewis
//

#ifndef  JSONARR_HPP_
# define JSONARR_HPP_

# include <list>
# include <string>
# include <stdexcept>
# include "IJson.hpp"

namespace				JSON
{
  class					JsonArr : public IJson, private JsonParser
  {
  public:
    JsonArr();
    JsonArr(JsonArr const &);
    ~JsonArr();
    
    IJson &				operator[](int index);
    
    void				AddObj(IJson const & val);
    std::list<IJson *> const &		GetList() const;
    std::list<IJson *> &		GetList();
    size_t				Size() const;
    std::string const &			Serialize();
    std::string const &			Serialize(int level);
    int					ParseFrom(std::string const & text);
    void				Clear();
    bool				Newline() const;
    IJson *				Clone() const;
    
  private:
    std::list<IJson *>			objs;
    std::string				serialized;
  };
};

#endif
