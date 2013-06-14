#ifndef TASKRUNNERFACTORY_H_
#define TASKRUNNERFACTORY_H_

#include "taskrunner.h"

class task_runner_factory {

public:
	task_runner* create_task_runner(int argc, char* argv[]);

};

#endif /* TASKRUNNERFACTORY_H_ */
