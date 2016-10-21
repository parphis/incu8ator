/**
 * Read out the temperature and the humidity values from a 
 * DHT22 sensor.
 */
#ifndef SENSORDHT22H
#define SENSORDHT22H

#include "sensorBase.h"

class sensorDHT22 : public sensorBase
{
private:
	void initSensor(void);
public:
	sensorDHT22(void);
	virtual ~sensorDHT22(void);
	void readOut(void);
	bool helloSensor(void);
};
#endif
