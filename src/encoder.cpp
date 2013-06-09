#include <iostream>
#include <fstream>
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

void encoder::get_input(int argc, char* argv[]) {
	string file = argv[1];

	ifstream t(file);
	stringstream buffer;
	buffer << t.rdbuf();

	this->_str = buffer.str();
}

void* encoder::get_sliced_input(int slice_index, int slice_count) {
	string* s = new string("");
	for (unsigned int i = slice_index; i < this->_str.length(); i += slice_count) {
		(*s) += this->_str[i];
	}
	return s;
}

void* encoder::get_output() {
	return NULL;
}

void encoder::process(void* input) {
	colorizer col;
	char_encoding enc;

	string str = *((string*) input);

	for (unsigned int i = 0; i < str.length(); i++) {
		char ch = str[i];
		unsigned long byte = enc.get_byte(ch);
		pair<rgb, rgb> colors = col.get_colors(byte);
		this->_colors.push_back(colors);
	}

}
