#include <iostream>
#include <string>
#include <cstring>
#include "incu8ator.h"
#include "utils.h"
#include "log.h"

void usage(void) {
	std::cout << "*** incu8ator ***" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "Usage:" << std::endl;
	std::cout << "nc8tr <sensorType> <displayType>" << std::endl;
	std::cout << "sensorType: the type of the temperature sensor connected. Currently available types are 'emulator' or 'dht22'. Emulator simply generates random temperature and humidity values." << std::endl;
	std::cout << "displayType: the type of the display connected. Enter 'stdout' to see the messages in your console or write 'OLED12864' if have this kind of OLED display connected." << std::endl;
}

int main(int argc, char* argv[]) {
	std::string sensorType = "emulator";
	std::string displayType = "stdout";
	/* check parameters */
	if(argc>=2) {
		if( (!strcmp(argv[1],"?")) ||
		(!strcmp(argv[1],"-?")) || 
		(!strcmp(argv[1],"-h")) || 
		(!strcmp(argv[1],"--help"))) {
			usage();
			return 0;
		}
		sensorType = argv[1];
	}
	if(argc>=3)
		displayType = argv[2];

	incu8ator *i = new incu8ator();

	// maybe this should be set up from a command line argument?
	log::_debug();

	// undetectable sensor or program wheel issue
	// both of them are mandatory to run the device
	if(!i->initIncu8ator(sensorType, displayType)) {
		delete i;
		return -1;
	}

	i->startIncu8ator();

	while(i->controlTemp()) {
		do_sleep(3);
	}

	delete i;

	return 0;
}
