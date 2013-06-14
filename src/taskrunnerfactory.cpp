#include <string.h>

#include "taskrunnerfactory.h"
#include "taskrunner.h"
#include "mpitaskrunner.h"
#include "simpletaskrunner.h"

task_runner* task_runner_factory::create_task_runner(int argc, char* argv[]) {

	if (argc > 2 && strcmp(argv[2], "mpi") == 0) {
		return new mpi_task_runner();
	}

	return new simple_task_runner();

}
