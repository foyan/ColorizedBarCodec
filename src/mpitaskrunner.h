#ifndef MPITASKRUNNER_H_
#define MPITASKRUNNER_H_

#include "taskrunner.h"
#include "task.h"

class mpi_task_runner : public task_runner {

public:
	void run(task* t, int argc, char* argv[]);

private:
	const int TAG = 123;
	const int MASTER = 0;

	void log(int rank, std::string message);

};

#endif /* MPITASKRUNNER_H_ */
