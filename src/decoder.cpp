#include <iostream>
#include <fstream>
#include <png++/png.hpp>
#include <boost/filesystem.hpp>

#include "decoder.h"
#include "colorizer.h"
#include "charencoding.h"
#include "rgb.h";

using namespace std;

void decoder::init(int argc, char* argv[]) {
	string file = argv[1];

	png::image image(file);

	for (int x = 0; x < 102; x += 3) {
		for (int y = 0; y < 100; y += 2) {
			png::rgb_pixel x0y0 = image.get_pixel(x+0, y+0);
			png::rgb_pixel x0y1 = image.get_pixel(x+0, y+1);
			png::rgb_pixel x1y0 = image.get_pixel(x+1, y+0);
			png::rgb_pixel x1y1 = image.get_pixel(x+1, y+1);
			png::rgb_pixel x2y0 = image.get_pixel(x+2, y+0);
			png::rgb_pixel x2y1 = image.get_pixel(x+2, y+1);

			rgb p1 = this->get_color(x0y0, x0y1, x1y0);
			rgb p2 = this->get_color(x2y0, x2y1, x1y1);

			this->_pixels.push_back(pair(p1, p2));
		}
	}

	boost::filesystem::path p;
	p /= file;

	this->_txt_filename = p.replace_extension(".txt").string();

}

rgb decoder::get_color(png::rgb_pixel m, png::rgb_pixel s1, png::rgb_pixel s2) {
	if (m == s1 || m == s2) {
		return rgb(m.red, m.green, m.blue);
	}
	if (s1 == s2) {
		return rgb(s1.red, s1.green, s1.blue);
	}
	return rgb(s2.red, s2.green, s2.blue);
}

void* decoder::get_sliced_input(int slice_index, int slice_count) {
	string* s = new string("");
	for (unsigned int i = slice_index; i < this->_str.length(); i += slice_count) {
		(*s) += this->_str[i];
	}
	return s;
}

void* decoder::process_slice(void* input) {
	colorizer col;
	char_encoding enc;

	string str = *((string*) input);
	vector<pair<rgb, rgb>>* result = new vector<pair<rgb, rgb>>();

	for (unsigned int i = 0; i < str.length(); i++) {
		char ch = str[i];
		unsigned long byte = enc.get_byte(ch);
		pair<rgb, rgb> colors = col.get_colors(byte);
		result->push_back(colors);
	}

	return result;
}

void decoder::collect_slice(void* slice, int slice_index, int slice_count) {
	vector<pair<rgb, rgb>> slice_vec = *((vector<pair<rgb, rgb>>*) slice);

	for (unsigned int i = 0; i < slice_vec.size(); i++) {

		unsigned int idx = (i*slice_count) + slice_index;
		while (this->_pixels.size() - 1 < idx || this->_pixels.size() == 0) {
			this->_pixels.push_back(pair<rgb, rgb>());
		}

		this->_pixels[idx] = slice_vec[i];
	}

}

void decoder::finalize() {
	png::image<png::rgb_pixel> image(102, 100);

	for (unsigned int i = 0; i < this->_pixels.size(); i++) {

		pair<rgb, rgb> pixel = this->_pixels[i];

		int x = (i*3) % 102;
		int y = (i*3) / 102 * 2;

		image.set_pixel(x+0, y+0, png::rgb_pixel(pixel.first.r(), pixel.first.g(), pixel.first.b()));
		image.set_pixel(x+1, y+0, png::rgb_pixel(pixel.first.r(), pixel.first.g(), pixel.first.b()));
		image.set_pixel(x+0, y+1, png::rgb_pixel(pixel.first.r(), pixel.first.g(), pixel.first.b()));
		image.set_pixel(x+1, y+1, png::rgb_pixel(pixel.second.r(), pixel.second.g(), pixel.second.b()));
		image.set_pixel(x+2, y+1, png::rgb_pixel(pixel.second.r(), pixel.second.g(), pixel.second.b()));
		image.set_pixel(x+2, y+0, png::rgb_pixel(pixel.second.r(), pixel.second.g(), pixel.second.b()));

	}

	image.write(this->_png_filename);
}

void decoder::pack_input(pack &p, void* data) {
	p.Str = *((string*)data);
}

void decoder::pack_output(pack &p, void* data) {
	p.Pixels = *((vector<pair<rgb, rgb> >*)data);
}

void* decoder::unpack_input(pack &p) {
	return new string(p.Str);
}

void* decoder::unpack_output(pack &p) {
	return new vector<pair<rgb, rgb> >(p.Pixels);
}

