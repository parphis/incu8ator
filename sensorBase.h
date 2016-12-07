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
	float temperature;
	float humidity;
	short int crcError;
	int crcErrorCounter;
	std::string errorString;
	int mGPIOPin;
	int mReadAlgorythm;
public:
	static sensorBase* createSensor(std::string type);
	sensorBase(void) : temperature(0.0), humidity(0.0), crcError(0), crcErrorCounter(0) {;}
	virtual ~sensorBase(void){;}
	virtual void readOut(void)=0;
	virtual bool helloSensor(void)=0;
	float getTemperature(void);
	float getHumidity(void);
	short int getCrcError(std::string& e);
	int getCrcErrorCounter(void);
	void getFormattedLines(std::string& lines);
	void setGPIOPin(int pin);
	void setAlgorythm(int a);
};
#endif
