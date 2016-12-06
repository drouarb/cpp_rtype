//
// Created by guemasg on 08/04/16.
//



#ifndef CPP_PLAZZA_THREAD_HPP
#define CPP_PLAZZA_THREAD_HPP

#include <pthread.h>
#include <stdarg.h>
#include <functional>
#include <vector>
#include <iostream>
#include "IThread.hpp"

template<typename T>
class Thread : public IThread<T>
{
private:
  typedef void *(*PthreadPtr)(void *);

  typedef void *(T::*t_member)(void *);

  typedef __gthread_t native_handle_type;
  native_handle_type _M_thread;
  State stat;

  struct s_fun
  {
    T *instance;
    t_member member;
    void *data;
  };

  static void *execute_thread(void *fun)
  {
    s_fun *f = static_cast<s_fun *>(fun);

    return (f->instance->*f->member)(f->data);
  }

public:
  Thread()
  {
    this->stat = State::NOTSTART;
  };


  Thread(void *(T::*pFunction)(void *), T *instance, void *data)
  {
    this->stat = State::NOTSTART;
    this->startThread(pFunction, instance, data);
  };

  ~Thread()
  {
  };

  State getStatus()
  {
    return this->stat;
  };

  native_handle_type getThread() const
  {
    return this->_M_thread;
  }

  void waitThread()
  {
  if (pthread_join(this->_M_thread, NULL))
    {
      throw (new std::runtime_error("Thread join failed"));
    }
    this->stat = State::DEAD;
  };

  void startThread(void *(T::*pFunction)(void *), T *instance, void *data)
  {
    s_fun *fun = new s_fun;

    fun->member = pFunction;
    fun->instance = instance;
    fun->data = data;
    if (pthread_create(&this->_M_thread, NULL, &execute_thread, fun) == 1)
      {
	throw (new std::runtime_error("Thread faild "));
      }
    this->stat = State::RUNNING;
  };

  Thread &operator=(const Thread &t)
  {
    this->_M_thread = t._M_thread;
    this->stat = t.stat;
    return (*this);
  };
};

#endif //CPP_ARCADE_THREAD_HPP
