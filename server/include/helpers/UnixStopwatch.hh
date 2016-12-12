//
// Timer.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:05:33 2016 Esteban Lewis
// Last update Fri May 27 19:19:52 2016 Esteban Lewis
//

#ifndef  UNIXSTOPWATCH_HPP_
# define UNIXSTOPWATCH_HPP_

# include "IStopwatch.hh"
# include <sys/time.h>
# include <time.h>

class			UnixStopwatch : public IStopwatch
  {
  public:
    UnixStopwatch();
    ~UnixStopwatch();
    
    void			set();
    long			ellapsedMs();
    
  private:
	  struct timeval		startTime;
};

#endif
