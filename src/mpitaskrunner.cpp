#include "mpitaskrunner.h"
#include "task.h"

void mpi_task_runner::run(task* t, int argc, char* argv[]) {
	t->init(argc, argv);

	void* slice_input = t->get_sliced_input(0, 1);

	void* slice_output = t->process_slice(slice_input);

	t->collect_slice(slice_output, 0, 1);

	t->finalize();
}
