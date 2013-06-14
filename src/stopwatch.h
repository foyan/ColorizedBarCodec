#ifndef STOPWATCH_H_
#define STOPWATCH_H_

class stopwatch {

public:
	stopwatch();
	void stop();
	long double elapsed() const;

private:
	long double _start;
	long double _end;

	long double get_real_time();

};

#endif /* STOPWATCH_H_ */
