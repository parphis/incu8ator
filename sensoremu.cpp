/**
 * Sensor emulator to test the measuring module.
 */
#include <cstdlib>
#include <time.h>
#include "sensoremu.h"

double sensorEmu::doubleRand(double min, double max) {
	srand(time(NULL));
	double f = (double)rand()/RAND_MAX;
	return min + (f*(max-min));
}
void sensorEmu::initSensor(void) {
	temperature = 0.1;
	humidity = 33.0;
	crcError = 0;
}
sensorEmu::sensorEmu(void) {
	initSensor();
	if(bcm2835_init()==false) {
		log::err("BCM2835 library initialization failed!");
	}
}
sensorEmu::~sensorEmu(void) {
}
void sensorEmu::readOut(void) {
	temperature = doubleRand(28.0, 45.0);
	humidity = doubleRand(40.0, 80.0);
	crcError = (int)doubleRand(0.0,2.0);
	if(crcError>0)	crcErrorCounter++;
	else	crcErrorCounter = 0;
}
bool sensorEmu::helloSensor(void) {
	return true;
}
