//
// Stopwatch.cpp for rtype in /home/lewis_e/rendu/cpp/cpp_rtype
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:11:08 2016 Esteban Lewis
// Last update Fri May 27 19:20:15 2016 Esteban Lewis
//

#include "helpers/IStopwatch.hh"

#ifdef _WIN32
#include "helpers/WindowsStopwatch.hh"
#else
#include "helpers/UnixStopwatch.hh"
#endif

IStopwatch * IStopwatch::getInstance()
{
#ifdef _WIN32
    return (new WindowsStopwatch());
#else
    return (new UnixStopwatch());
#endif
}