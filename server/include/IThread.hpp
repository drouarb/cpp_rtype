//
// IThread.hpp for IThread in /home/trouve_b/Desktop/CPP_project/cpp_rtype/tests_thr_pool
// 
// Made by Alexis Trouve
// Login   <trouve_b@epitech.net>
// 
// Started on  Wed Apr 13 11:07:26 2016 Alexis Trouve
// Last update Sat Apr 16 15:49:02 2016 Alexis Trouve
//

#ifndef ITHREAD_HPP_
# define ITHREAD_HPP_

enum State
{
  NOTSTART,
  RUNNING,
  DEAD
};

typedef void *(*handler)(void *);

template<typename T>
class IThread
{
 public:
  virtual ~IThread()
  { };

  virtual State getStatus() = 0;

  virtual void startThread(void *(T::*pFunction)(void *), T *instance,
			   void *data) = 0;

  virtual void waitThread() = 0;
};

#endif
