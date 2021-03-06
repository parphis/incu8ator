/**
 * Base class for the display "drivers".
 */
#ifndef	DISPLAYBASEH_
#define	DISPLAYBASEH_

#include <iostream>
#include <string>
#include "ArduiPi_SSD1306.h"
#include "Adafruit_SSD1306.h"

class displayBase {
public:
	static displayBase* createDisplay(std::string type);
	displayBase(void) {;}
	virtual ~displayBase(void) {;}
	virtual void showMessage(std::string const message)=0;
};
#endif
