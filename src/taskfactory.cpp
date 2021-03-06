#include <boost/filesystem.hpp>

#include "taskfactory.h"
#include "task.h"
#include "encoder.h"
#include "decoder.h"

using namespace std;

task* task_factory::create_task(int argc, char* argv[]) {

	string file = argv[1];

	boost::filesystem::path p;
	p /= file;

	string extension = p.extension().string();
	transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

	if (extension == ".png") {
		decoder* dec = new decoder();
		return dec;
	} else {
		encoder* enc = new encoder();
		return enc;
	}

}
