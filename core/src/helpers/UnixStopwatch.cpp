//
// Created by drouar_b on 12/19/16.
//

#include <sys/time.h>
#include "helpers/UnixStopwatch.hh"

helpers::UnixStopwatch::UnixStopwatch() {
	this->set();
}

helpers::UnixStopwatch::~UnixStopwatch() {

}

void helpers::UnixStopwatch::set() {
	gettimeofday(&startTime, NULL);
}

long helpers::UnixStopwatch::elapsedMs() {
	struct timeval checkTime;

	gettimeofday(&checkTime, NULL);
	return ((checkTime.tv_sec - startTime.tv_sec) * 1000 +
			(checkTime.tv_usec - startTime.tv_usec) / 1000);
}
