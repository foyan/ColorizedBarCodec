#include <iostream>
#include "encoder.h"

string encoder::str() {
	return this->_str;
}

void encoder::str(string s) {
	this->_str = s;
}

void* encoder::get_input

void* encoder::get_input(int slice_index, int slice_count) {
	string* s = new string("");
	for (unsigned int i = slice_index; i < this->_str.length(); i += slice_count) {
		(*s) += this->_str[i];
	}
	return s;
}

void* encoder::get_output() {
	return NULL;
}
