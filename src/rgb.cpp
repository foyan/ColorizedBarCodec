/*
 * rgb.cpp
 *
 *  Created on: Jun 6, 2013
 *      Author: florian
 */

#include "rgb.h"

rgb::rgb(short r, short g, short b) {
	this->_r = r;
	this->_g = g;
	this->_b = b;
}

rgb::rgb() : rgb(0, 0, 0) {

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

short rgb::r() {
	return this->_r;
}
short rgb::g() {
	return this->_g;
}
short rgb::b() {
	return this->_b;
}
