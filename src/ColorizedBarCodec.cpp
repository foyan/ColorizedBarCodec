#include <iostream>

#include "rgb.h"
#include "colorizer.h"
#include "charencoding.h"

using namespace std;

int main() {

	colorizer col;
	char_encoding enc;

	string str = "Hallo, jetzt kommt dann bald Fussball.";

	for (unsigned int i = 0; i < str.length(); i++) {
		char ch = str[i];
		unsigned long byte = enc.get_byte(ch);
		pair<rgb, rgb> colors = col.get_colors(byte);

		cout << ch << "=(" << colors.first << "/" << colors.second << ")" << endl;

	}


	return 0;
}
