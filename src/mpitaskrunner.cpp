#include <boost/mpi.hpp>
#include <boost/serialization/utility.hpp>

#include "mpitaskrunner.h"
#include "task.h"
#include "pack.h"
#include "stopwatch.h"

namespace mpi = boost::mpi;

void mpi_task_runner::run(task* t, int argc, char* argv[]) {

	mpi::environment env(argc, argv);
	mpi::communicator world;

	if (world.rank() == MASTER) {

		stopwatch sw;

		t->init(argc, argv);

		for (int rank = 0; rank < world.size(); rank++) {
			if (rank != MASTER) {
				void* slice_input = t->get_sliced_input(rank, world.size());

				pack ipack;
				t->pack_input(ipack, slice_input);

				world.isend(rank, TAG, ipack);
			}
		}

		void* my_slice = t->get_sliced_input(world.rank(), world.size());
		void* my_output = t->process_slice(my_slice);
		t->collect_slice(my_output, world.rank(), world.size());


		for (int rank = 0; rank < world.size(); rank++) {
			if (rank != MASTER) {
				pack opack;
				world.recv(rank, TAG, opack);

				void* slice_output = t->unpack_output(opack);
				t->collect_slice(slice_output, rank, world.size());
			}
		}

		t->finalize();

		sw.stop();
		cout << "MASTER node finished in " << sw.elapsed() << " ms." << endl;


	} else {

		stopwatch sw;

		pack ipack;
		world.recv(MASTER, TAG, ipack);
		void* slice_input = t->unpack_input(ipack);

		void* slice_output = t->process_slice(slice_input);

		pack opack;
		t->pack_output(opack, slice_output);
		world.isend(MASTER, TAG, opack);

		sw.stop();

		cout << "non-MASTER node #" << world.rank() << " finished in " << sw.elapsed() << " ms." << endl;

	}

}

void mpi_task_runner::log(int rank, std::string message) {
	std::cout << "#" << rank << ": " << message << std::endl;
	std::cout.flush();
}
