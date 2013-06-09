#ifndef MPITASKRUNNER_H_
#define MPITASKRUNNER_H_

#include "taskrunner.h"
#include "task.h"

class mpi_task_runner : public task_runner {

public:
	void run(task* t, int argc, char* argv[]);


};

#endif /* MPITASKRUNNER_H_ */
