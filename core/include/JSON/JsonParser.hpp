//
// JsonParser.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Wed Apr 20 11:26:38 2016 Esteban Lewis
// Last update Sun May 22 17:49:44 2016 Esteban Lewis
//

#ifndef  JSONPARSER_HPP_
# define JSONPARSER_HPP_

# include <string>

namespace			JSON
{
  class				JsonParser
  {
  public:
    JsonParser();
    virtual ~JsonParser();
      
  protected:
    int				txtAdv(std::string const & txt,
				       const char * chars,
				       int idx, int len);
    int				txtUpto(std::string const & txt,
					char c,
					int idx, int len);
    std::string			replaceAll(std::string txt,
					   std::string const & to_replace,
					   std::string const & replace_by);
      
    std::string			chars(char c, int n);
  };
};

#endif
