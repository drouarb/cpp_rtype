//
// UnixStopwatch.cpp for rtype in /home/lewis_e/rendu/cpp/cpp_rtype
// 
// Made by Esteban Lewis
// Login   <lewis_e@epitech.net>
// 
// Started on  Mon Apr 18 16:11:08 2016 Esteban Lewis
// Last update Fri May 27 19:20:15 2016 Esteban Lewis
//

#include "helpers/UnixStopwatch.hh"

UnixStopwatch::UnixStopwatch()
{ }

UnixStopwatch::~UnixStopwatch()
{ }

void
UnixStopwatch::set()
{
	gettimeofday(&startTime, NULL);
}

long
UnixStopwatch::ellapsedMs()
{
	struct timeval checkTime;

  gettimeofday(&checkTime, NULL);
  return ((checkTime.tv_sec - startTime.tv_sec) * 1000 +
	  (checkTime.tv_usec - startTime.tv_usec) / 1000);
}
