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
public:
	incu8ator(void);
	virtual ~incu8ator(void);
	bool initIncu8ator(std::string const sensorType, std::string const displayType);
	void startIncu8ator(void);
	bool controlTemp(void);
};
#endif
