#ifndef DECODER_H_
#define DECODER_H_

#include <iostream>
#include <vector>
#include "task.h"
#include "rgb.h"
#include <png++/png.hpp>
#

using namespace std;

class decoder : public task {

public:
	void init(int argc, char* argv[]);
	void* get_sliced_input(int slice_index, int slice_count);
	void* process_slice(void* input);
	void collect_slice(void* slice, int slice_index, int slice_count);
	void finalize();

	void pack_input(pack&, void*);
	void pack_output(pack&, void*);
	void* unpack_input(pack&);
	void* unpack_output(pack&);


private:
	string _str;
	string _txt_filename;
	vector<pair<rgb, rgb>> _pixels;

	rgb get_pixel(png::rgb_pixel m, png::rgb_pixel s1, png::rgb_pixel s2);

};

#endif /* DECODER_H_ */
