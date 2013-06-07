#include <unordered_map>

#include "colorizer.h"
#include "rgb.h"

colorizer::colorizer() {
	this->_nibbles.reset(new unordered_map<unsigned short, rgb>());

	(*this->_nibbles)[binary(0000)] = rgb(255, 0, 0);
	(*this->_nibbles)[binary(0001)] = rgb(0, 128, 0);
	(*this->_nibbles)[binary(0010)] = rgb(0, 0, 25);
	(*this->_nibbles)[binary(0011)] = rgb(165, 42, 42);
	(*this->_nibbles)[binary(0100)] = rgb(128, 0, 0);
	(*this->_nibbles)[binary(0101)] = rgb(100, 149, 237);
	(*this->_nibbles)[binary(0110)] = rgb(255, 165, 0);
	(*this->_nibbles)[binary(0111)] = rgb(255, 255, 0);
	(*this->_nibbles)[binary(1000)] = rgb(238, 130, 238);
	(*this->_nibbles)[binary(1001)] = rgb(128, 128, 128);
	(*this->_nibbles)[binary(1010)] = rgb(0, 0, 128);
	(*this->_nibbles)[binary(1011)] = rgb(0, 0, 0);
	(*this->_nibbles)[binary(1100)] = rgb(173, 255, 47);
	(*this->_nibbles)[binary(1101)] = rgb(138, 43, 226);
	(*this->_nibbles)[binary(1110)] = rgb(128, 0, 128);
	(*this->_nibbles)[binary(1111)] = rgb(95, 158, 160);

}

pair<rgb, rgb> colorizer::get_colors(unsigned short byte) {
	short low = byte & binary(00001111);
	short high = byte & binary(11110000) >> 4;

	return pair<rgb, rgb>((*this->_nibbles)[low], (*this->_nibbles)[high]);
}
