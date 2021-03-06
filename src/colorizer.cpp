#include <unordered_map>

#include "colorizer.h"
#include "rgb.h"

colorizer::colorizer() {
	this->_nibbles.reset(new nibble_bimap());

	this->_nibbles->insert(nibble_bimap::value_type(binary(0000), rgb(255, 0, 0)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(0001), rgb(0, 128, 0)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(0010), rgb(0, 0, 25)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(0011), rgb(165, 42, 42)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(0100), rgb(128, 0, 0)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(0101), rgb(100, 149, 237)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(0110), rgb(255, 165, 0)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(0111), rgb(255, 255, 0)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(1000), rgb(238, 130, 238)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(1001), rgb(128, 128, 128)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(1010), rgb(0, 0, 128)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(1011), rgb(0, 0, 0)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(1100), rgb(173, 255, 47)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(1101), rgb(138, 43, 226)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(1110), rgb(128, 0, 128)));
	this->_nibbles->insert(nibble_bimap::value_type(binary(1111), rgb(95, 158, 160)));

}

pair<rgb, rgb> colorizer::get_colors(unsigned short byte) {

	unsigned short low = byte & binary(00001111);
	unsigned short high = (byte & binary(11110000)) >> 4;

	rgb lcolor = this->_nibbles->left.at(low);
	rgb hcolor = this->_nibbles->left.at(high);

	return pair<rgb, rgb>(lcolor, hcolor);
}

unsigned short colorizer::get_byte(const rgb& low, const rgb& high) {
	unsigned short l = this->_nibbles->right.at(low);
	unsigned short h = this->_nibbles->right.at(high);

	unsigned short res = (h << 4) | l;

	return res;
}
