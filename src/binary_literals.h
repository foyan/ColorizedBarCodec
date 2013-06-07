#ifndef BINARY_LITERALS_H_
#define BINARY_LITERALS_H_

typedef unsigned long longest_t;

template<longest_t N>
class bin {

public:
        enum {
                value = (N % 8) + (bin<N / 8>::value << 1)
        };

};

template<>
class bin<0> {

public:
        enum {
                value = 0
        };

};

#define binary(n) bin<0##n>::value


#endif /* BINARY_LITERALS_H_ */
