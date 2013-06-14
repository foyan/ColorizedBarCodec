#include <iostream>
#include <memory>

#include "taskfactory.h"
#include "task.h"
#include "mpitaskrunner.h"

using namespace std;

int main(int argc, char* argv[]) {

	task_factory factory;

	std::auto_ptr<task> t(factory.create_task(argc, argv));

	mpi_task_runner r;

	r.run(t.get(), argc, argv);

	return 0;
}
