#include "simpletaskrunner.h"
#include "task.h"
#include "stopwatch.h"

void simple_task_runner::run(task* t, int argc, char* argv[]) {

	stopwatch sw;

	t->init(argc, argv);

	void* slice_input = t->get_sliced_input(0, 1);

	void* slice_output = t->process_slice(slice_input);

	t->collect_slice(slice_output, 0, 1);

	t->finalize();

	sw.stop();
	cout << "simple_task_runner finished in " << sw.elapsed() << " ms." << endl;

}
