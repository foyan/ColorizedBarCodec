#include <iostream>

#include "rgb.h"
#include "colorizer.h"
#include "charencoding.h"

#include <png++/png.hpp>

using namespace std;

int main() {

	colorizer col;
	char_encoding enc;

	string str = "Hallo, jetzt kommt dann bald Fussball. Fussball ist eine supercoole Geschichte. Ich mag Fussball. Fussball Fussball Fussbal!";

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

	}

	image.write("out.png");


	return 0;
}
