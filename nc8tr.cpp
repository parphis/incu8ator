#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <getopt.h>
#include "incu8ator.h"
#include "utils.h"
#include "log.h"

namespace {
	int debug_flag;
	int report_flag;
	const std::string version = "incu8ator v0.0.6.0 2016.";
}
void show_version(void) {
	std::cout << version << std::endl;
}
void usage(void) {
	std::cout << "*** incu8ator ***" << std::endl;
	std::cout << "-----------------" << std::endl;
	std::cout << "An egg incubator termostat implementation using Raspberry Pi." << std::endl;
	std::cout << "OLED12864 means an OLED type display having SSD1306 display driver." << std::endl << std::endl;
	std::cout << "Usage" << std::endl;
	std::cout << "nc8tr [OPTIONS]" << std::endl << std::endl;
	std::cout << "\t--sensortype <type>, -s <type>\tThe type of the temperature sensor connected. Currently available types are 'emulator' or 'dht22'. Emulator simply generates random temperature and humidity values." << std::endl;
	std::cout << "\t--displaytype <type>, -d <type>\tThe type of the display connected. Enter 'stdout' to see the messages in your console or write 'OLED12864' if you have this kind of OLED display connected." << std::endl;
	std::cout << "\t--sensorgpiopin <GPIO PIN#>, -p <GPIO PIN#>\tThe GPIO(!) pin number where the sensor connects. Default is GPIO04, that means the P1-07 physical connection." << std::endl;
	std::cout << "\t--qinterval <number>, -q <number>\tDelay between two sensor query in seconds. The default value is 10 seconds and maximum is also 10 seconds." << std::endl;
	std::cout << "\t--readalgorythm <number>, -a <number>\tMethod of query the sensor(DHT22). Currently there are two kind of options. Enter 1 to use the solution implemented by the Adafruit team(https://github.com/adafruit/Adafruit_Python_DHT). Or enter 2 to use a custom method gathered from the web from different sources. The first one is the best one." << std::endl;
	std::cout << "\t--maxtemp <number>, -m <number>\tTurn off the heating device when reaching the given temperature. Set it to a big number e.g. 9999 to avoid checking this limit(not recommended). For emergency purposes. Default value is 40.0°C." << std::endl;
	std::cout << "\t--maxsensorerror <number>, -e <number>\tThe maximum number of the consecutive sensor errors. The default value is 5. Assuming 10seconds as query interval this means that the heating device will be turned on not more than 50 seconds. An insulated box which is ca. 0.6m3 with a ceramic heating wire supplied with 240V causes ca. 1°C/15seconds temperature increase assuming 38°C as a starting temperature. Aboves mean that the final temperature will be ca. 42-43°C after the 5 consecutive sensor errors. Calculate this value based on your own box! Over 42°C eggs will die. Over 60°C there is a good chance to cause fire within the box!" << std::endl;
	std::cout << "\t--report\t\tCreates a CSV formatted file in /etc/incu8ator/report.csv. The will store each measuring steps as well as the errors." << std::endl;
	std::cout << "\t--debug\t\tWrite verbose log information into the syslog file. Use it only in case of error or first time check." << std::endl;
	std::cout << "\t--verbose\t\tSame as --debug." << std::endl;
	std::cout << "\t--help, -h\t\tShow this message." << std::endl;
	std::cout << "\t--version, -v\t\tShow version information." << std::endl << std::endl;
	std::cout << "Thanks to" << std::endl << std::endl;
	std::cout << "\tDHT22 driver - Adafruit tutorials on DHT22 and DHT11." << std::endl;
	std::cout << "\tOLED driver - http://github.com/hallard/ArduiPi_OLED" << std::endl;
	std::cout << "\tBCM2835 C library - airspayce.com/mikem/bcm2835" << std::endl << std::endl;
	std::cout << "PLEASE BE SURE YOU ARE ABSOLUTELY KNOW WHAT YOU DO! ENTERING WRONG OR INAPPROPRIATE COMMAND LINE PARAMETER VALUES MAY CAUSE FIRE IN YOUR INCUBATOR BOX. YOU MUST RUN MORE TESTS BEFORE LEAVING THE INCUBATOR BOX ALONE! TAKE INTO ACCOUNT THAT THE HEATING DEVICES AND THE SENSORS USED MAY VARY! PAPERS AND SEVERAL PLASTICS CAN FIRE UP FROM 80°C! EGGS DIE OVER 42°C. THE SUPPLY VOLTAGE (240V, 150V) OF AN INCUBATOR BOX IS VERY DANGEROUS!" << std::endl << std::endl;
	std::cout << "YOU ARE USING THIS SOFTWARE WITH ABSOLUTELY NO WARRANTY. I, THE OWNER OF THE SOURCE CODE, AM NOT RESPONSIBLE FOR ANY KIND OF ISSUES OR ACCIDENTS CAUSED BY THE SOFTWARE ITSELF - USE IT FOR YOUR OWN RISK!" << std::endl << std::endl;
	std::cout << "Istvan Vig (C) 2016." << std::endl;
}
bool processOptions(int argc, char *argv[], std::string& sensorType, std::string& displayType, int& sensorGPIOPin, int& queryInterval, int& readAlgorythm, double& maxTemp, int& maxSensorError) {
	int c;
	int option_index = 0;

	while(1) {
		static struct option long_options[] {
			{"verbose", no_argument, &debug_flag, 1},
			{"brief", no_argument, &debug_flag, 0},
			{"version", no_argument, 0, 'v'},
			{"debug", no_argument, &debug_flag, 1},
			{"release", no_argument, &debug_flag, 0},
			{"report", no_argument, &report_flag, 1},
			{"help", no_argument, 0, 'h'},
			{"sensortype", required_argument, 0, 's'},
			{"s", required_argument, 0, 's'},
			{"displaytype", required_argument, 0, 'd'},
			{"d", required_argument, 0, 'd'},
			{"sensorgpiopin", required_argument, 0, 'p'},
			{"p", required_argument, 0, 'p'},
			{"qinterval", required_argument, 0, 'q'},
			{"q", required_argument, 0, 'q'},
			{"readalgorythm", required_argument, 0, 'a'},
			{"a", required_argument, 0, 'a'},
			{"maxtemp", required_argument, 0, 'm'},
			{"m", required_argument, 0, 'm'},
			{"maxsensorerror", required_argument, 0, 'e'},
			{"e", required_argument, 0, 'e'},
			{0, 0, 0, 0},
		};

		c = getopt_long(argc, argv, "s:d:p:q:a:m:e:h", long_options, &option_index);

		if (c==-1)	break;

		switch(c) {
			case 0 : break;
			case 's': sensorType = optarg;	break;
			case 'd': displayType = optarg;	break;
			case 'p': sensorGPIOPin = atoi(optarg);	break;//RPI_V2_GPIO_P1_07 by default!
			case 'h': usage(); return false;
			case 'v': show_version(); return false;
			case 'q': queryInterval = atoi(optarg); break;// 10 by default!
			case 'a': readAlgorythm = atoi(optarg); break;// 1 by default!
			case 'm': maxTemp = atol(optarg); break;// 40.0 by default!
			case 'e': maxSensorError = atoi(optarg); break;//5 by default!
			case '?': break;
			default: abort();
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	std::string sensorType = "emulator";
	std::string displayType = "stdout";
	int sensorGPIOPin = RPI_V2_GPIO_P1_07; // means GPIO04!
	int queryInterval = 10;
	int readAlgorythm = 1; // query method of https://github.com/adafruit/Adafruit_Python_DHT
	double maxTemp = 40.0; // emergency limit
	int maxSensorError = 5; // emergency limit
	debug_flag = 0;
	report_flag = 0;

	if(!processOptions(argc, argv, sensorType, displayType, sensorGPIOPin, queryInterval, readAlgorythm, maxTemp, maxSensorError))
		return -1;

	// do not allow more than 10 seconds for query interval; please check the comment: incubator.cpp::controlTemp::checking the sensor error counter part!
	if(queryInterval>10)	queryInterval = 10;

	incu8ator *i = new incu8ator();

	// maybe this should be set up from a command line argument?
	std::string report_file = "/etc/incu8ator/report.csv\0";
	if (debug_flag) {
		log::_debug();
	}
	if (report_flag) {
		log::_report();
		log::_report_exist(access(report_file.c_str(), F_OK)==0 ? true : false);
		log::_report_name((const char*)report_file.c_str());
	}

	// undetectable sensor or program wheel issue
	// both of them are mandatory to run the device
	if(!i->initIncu8ator(sensorType, displayType, sensorGPIOPin, readAlgorythm, maxTemp, maxSensorError)) {
		delete i;
		return -1;
	}

	i->startIncu8ator();

	while(i->controlTemp()) {
		do_sleep(queryInterval);
	}

	delete i;

	// close (again) /dev/mem and all allocated memory
	// just to be sure
	bcm2835_close();

	return 0;
}
