//
// Created by greg on 16/12/2016.
//

#include "thread/Mutexer.hh"

Mutexer::Mutexer(IMutex *mutex) : mutex(mutex) {
    mutex->lock();
}

Mutexer::~Mutexer() {
    mutex->unlock();
}
