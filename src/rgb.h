#ifndef RGB_H_
#define RGB_H_

class rgb {

public:

	rgb(short, short, short);

	rgb();

	short r();
	short g();
	short b();

	void r(short);
	void g(short);
	void b(short);

private:
	short _r;
	short _g;
	short _b;
};

#endif /* RGB_H_ */
