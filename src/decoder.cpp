#include <iostream>
#include <fstream>
#include <png++/png.hpp>
#include <boost/filesystem.hpp>

#include "decoder.h"
#include "colorizer.h"
#include "charencoding.h"
#include "rgb.h"

using namespace std;

void decoder::init(int argc, char* argv[]) {
	string file = argv[1];

	png::image<png::rgb_pixel> img(file);

	int b = 0;
	int length = 0;
	int shift = 0;

	colorizer col;

	for (int y = 0; y < 100; y += 2) {
		for (int x = 0; x < 102; x += 3) {
			if (b >= length + 2) {
				continue;
			}
			png::rgb_pixel x0y0 = img.get_pixel(x+0, y+0);
			png::rgb_pixel x0y1 = img.get_pixel(x+0, y+1);
			png::rgb_pixel x1y0 = img.get_pixel(x+1, y+0);
			png::rgb_pixel x1y1 = img.get_pixel(x+1, y+1);
			png::rgb_pixel x2y0 = img.get_pixel(x+2, y+0);
			png::rgb_pixel x2y1 = img.get_pixel(x+2, y+1);

			rgb p1 = this->get_color(x0y0, x0y1, x1y0);
			rgb p2 = this->get_color(x2y0, x2y1, x1y1);

			pair<rgb, rgb> pr(p1, p2);

			if (b >= 2) {
				this->_pixels.push_back(pr);
			} else {
				length += (col.get_byte(pr.first, pr.second) << shift);
				shift += 8;
				std::cout << "LENGTH:" << length << "]" << std::endl;
			}

			b++;

		}
	}

	boost::filesystem::path p;
	p /= file;

	this->_txt_filename = p.replace_extension(".txt").string();

}

rgb decoder::get_color(png::rgb_pixel m, png::rgb_pixel s1, png::rgb_pixel s2) {
	if (this->is_equal(m, s1) || this->is_equal(m, s2)) {
		return rgb(m.red, m.green, m.blue);
	}
	if (this->is_equal(s1, s2)) {
		return rgb(s1.red, s1.green, s1.blue);
	}
	return rgb(s2.red, s2.green, s2.blue);
}

bool decoder::is_equal(const png::rgb_pixel& a, const png::rgb_pixel& b) {
	return a.blue == b.blue && a.green == b.green && a.red == b.red;
}

void* decoder::get_sliced_input(int slice_index, int slice_count) {
	vector<pair<rgb, rgb> >* px = new vector<pair<rgb, rgb> >();
	for (unsigned int i = slice_index; i < this->_pixels.size(); i += slice_count) {
		px->push_back(this->_pixels[i]);
	}
	return px;
}

void* decoder::process_slice(void* input) {
	colorizer col;
	char_encoding enc;

	vector<pair<rgb, rgb> >* px = (vector<pair<rgb, rgb> >*) input;

	string* result = new string("");

	for (unsigned int i = 0; i < px->size(); i++) {
		unsigned short byte = col.get_byte(px->at(i).first, px->at(i).second);
		(*result) += enc.get_char(byte);
	}

	return result;
}

void decoder::collect_slice(void* slice, int slice_index, int slice_count) {

	string slice_string = *((string*) slice);

	for (unsigned int i = 0; i < slice_string.length(); i++) {

		unsigned int idx = (i*slice_count) + slice_index;
		while (this->_str.length() - 1 < idx || this->_str.length() == 0) {
			this->_str += "_";
		}

		this->_str[idx] = slice_string[i];
	}

}

void decoder::finalize() {
	std::cout << "[" << this->_str << "]" << std::endl;
}

void decoder::pack_input(pack &p, void* data) {
	p.Pixels = *((vector<pair<rgb, rgb> >*)data);
}

void decoder::pack_output(pack &p, void* data) {
	p.Str = *((string*)data);
}

void* decoder::unpack_input(pack &p) {
	return new vector<pair<rgb, rgb> >(p.Pixels);
}

void* decoder::unpack_output(pack &p) {
	return new string(p.Str);
}

