//
// Created by greg on 11/12/2016.
//

#ifndef THREADTEST_THREAD_HH
#define THREADTEST_THREAD_HH


#include <thread>
#include "IThread.hh"

template<typename C, typename Param>
class Thread : public IThread {
private:
    std::thread *thread;
public:

    Thread(C c, Param p) {
        this->thread = new std::thread(c, p);
    }

    virtual ~Thread() {
        delete (thread);
    }

    bool joinable() override {
        return thread->joinable();
    }

    void join() override {
        thread->join();
    }

    void detach() override {
        thread->detach();
    }
};

#endif //THREADTEST_THREAD_HH
