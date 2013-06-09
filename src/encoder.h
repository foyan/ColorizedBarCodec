#ifndef ENCODER_H_
#define ENCODER_H_

#include <iostream>
#include <vector>
#include "task.h"
#include "rgb.h"

using namespace std;

class encoder : public task {

public:
	void get_input(int argc, char* argv[]);
	void* get_sliced_input(int slice_index, int slice_count);
	void* get_output();
	void process(void* input);

	string str();
	void str(string);

private:
	string _str;
	vector<pair<rgb, rgb>> _colors;

};

#endif /* ENCODER_H_ */
