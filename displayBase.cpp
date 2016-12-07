#include "displayBase.h"
#include "displayStdOut.h"
#include "displayOLED.h"

displayBase* displayBase::createDisplay(std::string type) {
	if(type=="stdout")
		return new displayStdOut;
	if(type=="OLED12864")
		return new displayOLED;
	return NULL;
}
