#include <iostream>

#include "taskfactory.h"
#include "task.h"
#include "simpletaskrunner.h"

using namespace std;

int main(int argc, char* argv[]) {

	task_factory factory;
	task* t = factory.create_task(argc, argv);

	simple_task_runner r;

	r.run(t, argc, argv);

	delete t;

	return 0;
}
