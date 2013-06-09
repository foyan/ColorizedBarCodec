#include <iostream>

#include "taskfactory.h"
#include "task.h"

using namespace std;

int main(int argc, char* argv[]) {

	task_factory factory;
	task* t = factory.create_task(argc, argv);

	t->init(argc, argv);

	void* slice_input = t->get_sliced_input(0, 1);

	void* slice_output = t->process_slice(slice_input);

	t->collect_slice(slice_output, 0, 1);

	t->finalize();

	delete t;

	return 0;
}
