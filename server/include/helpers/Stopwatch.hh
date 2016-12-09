//
// Timer.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:05:33 2016 Esteban Lewis
// Last update Fri May 27 19:19:52 2016 Esteban Lewis
//

#ifndef  STOPWATCH_HPP_
# define STOPWATCH_HPP_

#ifdef _WIN32
#include <Windows.h>
#else
# include <sys/time.h>
#endif
# include <time.h>

class			Stopwatch
  {
  public:
    Stopwatch();
    ~Stopwatch();
    
    void			set();
    long			ellapsedMs();
    
  private:
#ifdef _WIN32
	  unsigned long         tick;
#else
	  struct timeval		startTime;
#endif
};

#endif
