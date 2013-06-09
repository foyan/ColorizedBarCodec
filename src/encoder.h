#ifndef ENCODER_H_
#define ENCODER_H_

#include <iostream>
#include <vector>
#include "task.h"
#include "rgb.h"

using namespace std;

class encoder : public task {

public:
	void init(int argc, char* argv[]);
	void* get_sliced_input(int slice_index, int slice_count);
	void* process_slice(void* input);
	void collect_slice(void* slice, int slice_index, int slice_count);
	void finalize();

	string str();
	void str(string);


private:
	string _str;
	string _png_filename;
	vector<pair<rgb, rgb>> _pixels;

};

#endif /* ENCODER_H_ */
