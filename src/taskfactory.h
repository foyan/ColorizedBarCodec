#ifndef TASKFACTORY_H_
#define TASKFACTORY_H_

#include "task.h"

class task_factory {

public:
	task* create_task(int argc, char* argv[]);

};

#endif /* TASKFACTORY_H_ */
