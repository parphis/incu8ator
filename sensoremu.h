/**
 * DHT22 emulator to make the incubator tests faster and 
 * more independent from the hardwares.
 */
#ifndef DHT22EMUH
#define DHT22EMUH

#include "sensorBase.h"

class sensorEmu : public sensorBase
{
private:
	double doubleRand(double min, double max);
	void initSensor(void);
public:
	sensorEmu(void);
	virtual ~sensorEmu(void);
	void readOut(void);
	bool helloSensor(void);
};
#endif
