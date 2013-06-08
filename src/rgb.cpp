#include <iostream>
#include "rgb.h"

using namespace std;

rgb::rgb(short r, short g, short b) {
	this->_r = r;
	this->_g = g;
	this->_b = b;
}

rgb::rgb() {
	this->_r = 0;
	this->_g = 0;
	this->_b = 0;
}

void rgb::r(short r) {
	this->_r = r;
}
void rgb::b(short b) {
	this->_b = b;
}
void rgb::g(short g) {
	this->_g = g;
}

short rgb::r() const {
	return this->_r;
}
short rgb::g() const {
	return this->_g;
}
short rgb::b() const {
	return this->_b;
}

ostream& operator<<(ostream &stream, const rgb &a) {
	return stream << "rgb(" << a.r() << "," << a.g() << "," << a.b() << ")";
}

