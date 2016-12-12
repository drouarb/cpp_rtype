//
// Timer.hpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:05:33 2016 Esteban Lewis
// Last update Fri May 27 19:19:52 2016 Esteban Lewis
//

#ifdef _WIN32
#ifndef  WINSTOPWATCH_HPP_
# define WINSTOPWATCH_HPP_

#include "IStopwatch.hh"
#include <Windows.h>
#include <time.h>

class			WindowsStopwatch : public IStopwatch
  {
  public:
    WindowsStopwatch();
    ~WindowsStopwatch();
    
    void			set();
    long			ellapsedMs();
    
  private:
	  unsigned long         tick;
};

#endif
#endif