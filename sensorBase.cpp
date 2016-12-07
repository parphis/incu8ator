#include "sensorBase.h"
#include "sensoremu.h"
#include "sensorDHT22.h"

float sensorBase::getTemperature(void) {
	return temperature;
}
float sensorBase::getHumidity(void) {
	return humidity;
}
short int sensorBase::getCrcError(std::string& e) {
	e = errorString;
	return crcError;
}
int sensorBase::getCrcErrorCounter(void) {
	return crcErrorCounter;
}
void sensorBase::setGPIOPin(int pin) {
	mGPIOPin = pin;
}
void sensorBase::setAlgorythm(int a) {
	mReadAlgorythm = a;
}
sensorBase* sensorBase::createSensor(std::string type) {
	if(type=="emulator")
		return new sensorEmu;
	if(type=="dht22")
		return new sensorDHT22;
	return NULL;
}
void sensorBase::getFormattedLines(std::string& lines) {
	std::ostringstream os;
	os << temperature << "C " << humidity << "% " << (crcError ? "Sensor read error" : "");
	lines = os.str();
}
