/**
 * Read out the temperature and the humidity values from a 
 * DHT22 sensor.
 */
#ifndef SENSORDHT22H
#define SENSORDHT22H

#include <cstring>
#include <unistd.h>
#include <fstream>
#include <chrono>
#include "bcm2835.h"
#include "sensorBase.h"
#include "log.h"
#include "utils.h"
#include "pi_2_dht_read.h"

class sensorDHT22 : public sensorBase
{
private:
	template<class T>
	void dbg(T *pulses, T *lvls, int m);
	// This is the only processor specific magic value, the maximum amount of time to
	// spin in a loop before bailing out and considering the read a timeout.  This should
	// be a high value, but if you're running on a much faster platform than a Raspberry
	// Pi or Beaglebone Black then it might need to be increased.
	const uint32_t DHT_MAXCOUNT=8000;

	// Number of bit pulses to expect from the DHT.  Note that this is 41 because
	// the first pulse is a constant 50 microsecond pulse, with 40 pulses to represent
	// the data afterwards.
	const int DHT_PULSES=41;

	void adafruitRead(void);
	void customRead(void); 
	void doCalc(uint8_t data[5]);
public:
	sensorDHT22(void);
	virtual ~sensorDHT22(void);
	void readOut(void);
	bool helloSensor(void);
};
#endif
