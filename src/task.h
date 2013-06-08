#ifndef TASK_H_
#define TASK_H_

class task {

public:
	virtual void* get_input(int argc, char* argv[]) = 0;

	virtual void* get_sliced_input(int slice_count, int slice_index) = 0;

	virtual void* get_output() = 0;

	virtual ~task() {

	};

};

#endif /* TASK_H_ */
