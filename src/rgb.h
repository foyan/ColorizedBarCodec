#ifndef RGB_H_
#define RGB_H_

#include <iostream>

class rgb {

public:

	rgb(short, short, short);

	rgb();

	short r() const;
	short g() const;
	short b() const;

	void r(short);
	void g(short);
	void b(short);

	friend std::ostream& operator<<(std::ostream &stream, const rgb &a);

private:
	short _r;
	short _g;
	short _b;
};

namespace std {

	template<> struct less<rgb> {
		bool operator() (const rgb& a, const rgb& b) {
			return a.r() < b.r() || a.g() < b.g() || a.b() < b.b();
		}
	};

}

#endif /* RGB_H_ */
