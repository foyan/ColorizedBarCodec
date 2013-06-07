#include <iostream>

#include "rgb.h"
#include "colorizer.h"

using namespace std;

int main() {

	colorizer col;
	pair<rgb, rgb> colors = col.get_colors('K');

	cout << colors.first << "/" << colors.second << endl;

	return 0;
}
