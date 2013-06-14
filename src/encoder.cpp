#include <iostream>
#include <fstream>
#include <png++/png.hpp>
#include <boost/filesystem.hpp>

#include "encoder.h"
#include "colorizer.h"
#include "charencoding.h"

using namespace std;

string encoder::str() {
	return this->_str;
}

void encoder::str(string s) {
	this->_str = s;
}

void encoder::init(int argc, char* argv[]) {
	string file = argv[1];

	ifstream t(file);
	stringstream buffer;
	buffer << t.rdbuf();

	string s = buffer.str();

	this->_str = this->encode_header(s.length()) + buffer.str();

	boost::filesystem::path p;
	p /= file;

	this->_png_filename = p.replace_extension(".png").string();

}

void* encoder::get_sliced_input(int slice_index, int slice_count) {
	string* s = new string("");
	for (unsigned int i = slice_index; i < this->_str.length(); i += slice_count) {
		(*s) += this->_str[i];
	}
	return s;
}

void* encoder::process_slice(void* input) {
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

void encoder::collect_slice(void* slice, int slice_index, int slice_count) {
	vector<pair<rgb, rgb>> slice_vec = *((vector<pair<rgb, rgb>>*) slice);

	for (unsigned int i = 0; i < slice_vec.size(); i++) {

		unsigned int idx = (i*slice_count) + slice_index;
		while (this->_pixels.size() - 1 < idx || this->_pixels.size() == 0) {
			this->_pixels.push_back(pair<rgb, rgb>());
		}

		this->_pixels[idx] = slice_vec[i];
	}

}

void encoder::finalize() {
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

string encoder::encode_header(long long length) {
	char seq[] = {
			(length & binary(0000000011111111)) >> 0,
			(length & binary(1111111100000000)) >> 8

	};
	return string(seq);
}

void encoder::pack_input(pack &p, void* data) {
	p.Str = *((string*)data);
}

void encoder::pack_output(pack &p, void* data) {
	p.Pixels = *((vector<pair<rgb, rgb> >*)data);
}

void* encoder::unpack_input(pack &p) {
	return new string(p.Str);
}

void* encoder::unpack_output(pack &p) {
	return new vector<pair<rgb, rgb> >(p.Pixels);
}

