#ifndef COLORIZER_H_
#define COLORIZER_H_

#include <memory>
#include <unordered_map>
#include "binary_literals.h"
#include "rgb.h"

using namespace std;

class colorizer {

public:
	colorizer();
	pair<rgb, rgb> get_colors(unsigned short);

private:
	unique_ptr<unordered_map<unsigned short, rgb>> _nibbles;

};

#endif /* COLORIZER_H_ */
