//
// WindowsStopwatch.cpp for plazza in /home/lewis_e/rendu/cpp/cpp_plazza
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:11:08 2016 Esteban Lewis
// Last update Fri May 27 19:20:15 2016 Esteban Lewis
//

#ifdef _WIN32
#include "helpers/WindowsStopwatch.hh"

WindowsStopwatch::WindowsStopwatch()
{ }

WindowsStopwatch::~WindowsStopwatch()
{ }

void
WindowsStopwatch::set()
{
	tick = static_cast<unsigned long>(GetTickCount());
}

long
WindowsStopwatch::ellapsedMs()
{
	return (static_cast<unsigned long>(GetTickCount()) - tick);
}
#endif