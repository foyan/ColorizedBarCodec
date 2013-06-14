#include "stopwatch.h"
#include <sys/time.h>
#include <ctime>

stopwatch::stopwatch() {
	this->_start = this->get_real_time();
	this->_end = 0;
}

void stopwatch::stop() {
	this->_end = this->get_real_time();
}

long double stopwatch::elapsed() const {
	return this->_end - this->_start;
}

long double stopwatch::get_real_time() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long double millis = tv.tv_usec / 1000.0 + tv.tv_sec;

	return millis;
}
