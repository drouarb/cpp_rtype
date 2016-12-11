//
// Created by greg on 11/12/2016.
//

#include "../../include/thread/Mutex.hh"

Mutex::Mutex() {
    this->m = new std::mutex();
}

void Mutex::lock() {
    this->m->lock();
}

bool Mutex::tryLock() {
    return this->m->try_lock();;
}

void Mutex::unlock() {
    this->m->unlock();
}
