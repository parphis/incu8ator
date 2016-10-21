/**
 * Base class to implement the communication between 
 * a Raspberry Pi and a temperature/humidity sensor.
 */
#ifndef SENSORBASEH
#define SENSORBASEH

#include <string>
#include <sstream> //to convert double to string

class sensorBase {
protected:
	double temperature;
	double humidity;
	short int crcError;
public:
	static sensorBase* createSensor(std::string type);
	sensorBase(void) : temperature(0.0), humidity(0.0), crcError(0) {;}
	virtual ~sensorBase(void){;}
	virtual void readOut(void)=0;
	virtual bool helloSensor(void)=0;
	double getTemperature(void);
	double getHumidity(void);
	short int getCrcError(void);
	void getFormattedLines(std::string& lines);
};
#endif
