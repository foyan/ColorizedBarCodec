#include "mpitaskrunner.h"
#include "task.h"
#include "pack.h"
#include <boost/mpi.hpp>
#include <boost/serialization/utility.hpp>

namespace mpi = boost::mpi;

void mpi_task_runner::run(task* t, int argc, char* argv[]) {

	mpi::environment env(argc, argv);
	mpi::communicator world;

	if (world.rank() == 0) {
		t->init(argc, argv);

		for (int rank = 1; rank < world.size(); rank++) {
			void* slice_input = t->get_sliced_input(rank, world.size());

			pack ipack;
			t->pack_input(ipack, slice_input);

			world.send(rank, 123, ipack);

			pack opack;

			world.recv(rank, 123, opack);

			void* slice_output = t->unpack_output(opack);
			t->collect_slice(slice_output, 0, 1);
		}

	} else {

		pack ipack;
		world.recv(0, 123, ipack);
		void* slice_input = t->unpack_input(ipack);

		void* slice_output = t->process_slice(slice_input);

		pack opack;
		t->pack_output(opack, slice_output);
		world.send(0, 123, opack);

	}

	t->finalize();
}
