//
// Timer.hpp for rtype in /home/lewis_e/rendu/cpp/cpp_rtype
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:05:33 2016 Esteban Lewis
// Last update Fri May 27 19:19:52 2016 Esteban Lewis
//

#ifndef  STOPWATCH_HPP_
# define STOPWATCH_HPP_

class			IStopwatch
{
  public:
    virtual ~IStopwatch() { };
    
    virtual void			set() = 0;
    virtual long			ellapsedMs() = 0;

    static IStopwatch * getInstance();
};

#endif
