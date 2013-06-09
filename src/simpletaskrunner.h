#ifndef SIMPLETASKRUNNER_H_
#define SIMPLETASKRUNNER_H_

#include "taskrunner.h"
#include "task.h"

class simple_task_runner : public task_runner {

public:
	void run(task* t, int argc, char* argv[]);

};

#endif /* SIMPLETASKRUNNER_H_ */
