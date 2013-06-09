#ifndef TASK_H_
#define TASK_H_

#include <vector>
#include "rgb.h"
#include "pack.h"

using namespace std;

class task {

public:
	virtual void init(int argc, char* argv[]) = 0;
	virtual void* get_sliced_input(int slice_index, int slice_count) = 0;
	virtual void* process_slice(void* input) = 0;
	virtual void collect_slice(void* slice, int slice_index, int slice_count) = 0;
	virtual void finalize() = 0;

	virtual void pack_input(pack&, void*) = 0;
	virtual void pack_output(pack&, void*) = 0;
	virtual void* unpack_input(pack&) = 0;
	virtual void* unpack_output(pack&) = 0;

	virtual ~task() {

	}

};

#endif /* TASK_H_ */
