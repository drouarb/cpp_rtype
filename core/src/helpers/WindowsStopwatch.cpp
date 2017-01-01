//
// Created by drouar_b on 12/19/16.
//

#include "helpers/WindowsStopwatch.hh"

helpers::WindowsStopwatch::WindowsStopwatch() {
    this->set();
}

helpers::WindowsStopwatch::~WindowsStopwatch() {

}

void helpers::WindowsStopwatch::set() {
    tick = static_cast<unsigned long>(GetTickCount64());
}

long helpers::WindowsStopwatch::elapsedMs() {
    return (static_cast<unsigned long>(GetTickCount64()) - tick);
}

