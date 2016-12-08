/**
 * The controller class for the incu8ator project.
 * It's main task is to set the needed temperature 
 * based on the program-wheel by switching on and off 
 * the heating-thread using a GPIO port.
 */
#ifndef _INCU8ATORH_
#define _INCU8ATORH_

#include <iostream>
#include <sstream>
#include <time.h>
#include <iomanip>
#include "sensorBase.h"
#include "displayBase.h"
#include "programWheel.h"
#include "log.h"

class incu8ator {
private:
	bool dbg;
	sensorBase *s;
	displayBase *d; 
	programWheel *p;
	bool heating;
	double prevTemp;
	double maxTemp;
	int maxSensorError;
	int _heatGPIOPin;
	inline void clearSS(std::stringstream& ss);
	void sdt(std::string& s);
	void toogleHeating(int level);
	void heatOn(void);
	void heatOff(void);
public:
	incu8ator(void);
	virtual ~incu8ator(void);
	bool initIncu8ator(std::string const sensorType, std::string const displayType, int sensorGPIOPin, int heatGPIOPin, int readAlgorythm, double maxt, int maxse);
	void startIncu8ator(void);
	bool controlTemp(void);
};
#endif
