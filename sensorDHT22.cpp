#include "sensorDHT22.h"

void sensorDHT22::initSensor(void) {
	temperature = 0.1;
	humidity = 33.0;
	crcError = 0;
}
sensorDHT22::sensorDHT22(void) {
	initSensor();
}
sensorDHT22::~sensorDHT22(void) {
}
void sensorDHT22::readOut(void) {
	temperature = 100.0;
	humidity = 50;
	crcError = 0;
}
bool sensorDHT22::helloSensor(void) {
	return true;
}
