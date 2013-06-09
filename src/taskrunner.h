#ifndef TASKRUNNER_H_
#define TASKRUNNER_H_

#include "task.h"

class task_runner {

public:
	virtual void run(task* t, int argc, char* argv[]) = 0;

	virtual ~task_runner() {

	}

};

#endif /* TASKRUNNER_H_ */
