#include <iostream>
#include <unordered_map>

#include "rgb.h"
#include "binary_literals.h"

using namespace std;

int main() {

	unordered_map<short, rgb> nibbles;

	nibbles[binary(0000)] = rgb(255, 0, 0);
	nibbles[binary(0001)] = rgb(0, 128, 0);
	nibbles[binary(0010)] = rgb(0, 0, 25);
	nibbles[binary(0011)] = rgb(165, 42, 42);
	nibbles[binary(0100)] = rgb(0, 0, 0);
	nibbles[binary(0101)] = rgb(0, 0, 0);
	nibbles[binary(0110)] = rgb(0, 0, 0);
	nibbles[binary(0111)] = rgb(0, 0, 0);
	nibbles[binary(1000)] = rgb(0, 0, 0);
	nibbles[binary(1001)] = rgb(0, 0, 0);
	nibbles[binary(1010)] = rgb(0, 0, 0);
	nibbles[binary(1011)] = rgb(0, 0, 0);
	nibbles[binary(1100)] = rgb(0, 0, 0);
	nibbles[binary(1101)] = rgb(0, 0, 0);
	nibbles[binary(1110)] = rgb(0, 0, 0);
	nibbles[binary(1111)] = rgb(0, 0, 0);


	return 0;
}
