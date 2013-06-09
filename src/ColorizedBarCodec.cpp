#include <iostream>

#include "rgb.h"
#include "colorizer.h"
#include "charencoding.h"
#include "taskfactory.h"
#include "task.h"

#include <png++/png.hpp>
#include <boost/filesystem.hpp>

using namespace std;

int main(int argc, char* argv[]) {

	task_factory factory;
	task* t = factory.create_task(argc, argv);

	t->get_input(argc, argv);

	void* slice = t->get_sliced_input(1, 0);

	t->process(slice);

	/*colorizer col;
	char_encoding enc;

	png::image<png::rgb_pixel> image(102, 100);

	for (unsigned int i = 0; i < str.length(); i++) {
		char ch = str[i];
		unsigned long byte = enc.get_byte(ch);
		pair<rgb, rgb> colors = col.get_colors(byte);

		int x = (i*3) % 102;
		int y = (i*3) / 102 * 2;

		image.set_pixel(x+0, y+0, png::rgb_pixel(colors.first.r(), colors.first.g(), colors.first.b()));
		image.set_pixel(x+1, y+0, png::rgb_pixel(colors.first.r(), colors.first.g(), colors.first.b()));
		image.set_pixel(x+0, y+1, png::rgb_pixel(colors.first.r(), colors.first.g(), colors.first.b()));
		image.set_pixel(x+1, y+1, png::rgb_pixel(colors.second.r(), colors.second.g(), colors.second.b()));
		image.set_pixel(x+2, y+1, png::rgb_pixel(colors.second.r(), colors.second.g(), colors.second.b()));
		image.set_pixel(x+2, y+0, png::rgb_pixel(colors.second.r(), colors.second.g(), colors.second.b()));

	}*/

	delete t;

	//image.write("out.png");


	return 0;
}
