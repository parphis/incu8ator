/**
 * Wrapper class for the ArduiPi_SSD1306 library.
 * http://github.com/hallard/ArduiPi_OLED
 * 
 */
#ifndef	DISPLAYOLEDH_
#define	DISPLAYOLEDH_
#include <iostream>
#include <string>
//#include "ArduiPi_SSD1306.h"
//#include "Adafruit_SSD1306.h"
#include "displayBase.h"
#include "log.h"

class displayOLED : public displayBase {
private:	
	bool _init(void);
	bool mAvailable;
public:
	Adafruit_SSD1306 display;
	displayOLED(void);
	virtual ~displayOLED(void){;}
	void showMessage(std::string const message);
};
#endif
