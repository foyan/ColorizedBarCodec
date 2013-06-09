#ifndef PACK_H_
#define PACK_H_

#include <vector>
#include <string>
#include "rgb.h"

using namespace std;

class pack {

public:
	string Str;
	vector<pair<rgb, rgb>> Pixels;

};

namespace boost {
	namespace serialization {

		template<typename Archive>
		void serialize (Archive& ar, pack& r, const unsigned int version) {
			ar & r.Str;
			ar & r.Pixels;
		}

	}
}

#endif /* PACK_H_ */
