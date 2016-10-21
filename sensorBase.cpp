#include "sensorBase.h"
#include "sensoremu.h"
#include "sensorDHT22.h"

double sensorBase::getTemperature(void) {
	return temperature;
}
double sensorBase::getHumidity(void) {
	return humidity;
}
short int sensorBase::getCrcError(void) {
	return crcError;
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
	os << temperature << "°C\n" << humidity << "%\n" << (crcError ? "Sensor read error\n" : "");
	lines = os.str();
}
