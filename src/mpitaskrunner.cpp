#include "mpitaskrunner.h"
#include "task.h"
#include <boost/mpi.hpp>

namespace mpi = boost::mpi;

void mpi_task_runner::run(task* t, int argc, char* argv[]) {

	mpi::environment env(argc, argv);
	mpi::communicator world;

	if (world.rank() == 0) {
		t->init(argc, argv);

		for (int rank = 1; rank < world.size(); rank++) {
			void* slice_input = t->get_sliced_input(rank, world.size());
			world.send(rank, 123, slice_input);

			void* slice_output;
			world.recv(rank, 123, slice_output);
			t->collect_slice(slice_output, 0, 1);
		}

	} else {

		void* slice_input;
		world.recv(0, 123, slice_input);
		void* slice_output = t->process_slice(slice_input);
		world.send(0, 123, slice_output);

	}

	t->finalize();
}
