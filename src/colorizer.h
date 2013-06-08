#ifndef COLORIZER_H_
#define COLORIZER_H_

#include <memory>
#include <unordered_map>
#include <boost/bimap.hpp>
#include "binary_literals.h"
#include "rgb.h"

using namespace std;

typedef boost::bimap<unsigned short, rgb> nibble_bimap;

class colorizer {

public:
	colorizer();
	pair<rgb, rgb> get_colors(unsigned short);
	unsigned short get_byte(const rgb&, const rgb&);

private:
	unique_ptr<nibble_bimap> _nibbles;

};

#endif /* COLORIZER_H_ */
