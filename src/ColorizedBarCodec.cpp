#include <iostream>
#include <memory>

#include "taskfactory.h"
#include "task.h"
#include "taskrunner.h"
#include "taskrunnerfactory.h"

using namespace std;

int main(int argc, char* argv[]) {

	task_factory factory;
	task_runner_factory rfactory;

	std::auto_ptr<task_runner> r(rfactory.create_task_runner(argc, argv));
	std::auto_ptr<task> t(factory.create_task(argc, argv));

	r->run(t.get(), argc, argv);

	return 0;
}
