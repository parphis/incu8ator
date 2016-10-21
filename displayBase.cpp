#include "displayBase.h"
#include "displayStdOut.h"

displayBase* displayBase::createDisplay(std::string type) {
	if(type=="stdout")
		return new displayStdOut;
	if(type=="OLED12864")
		return NULL;
	return NULL;
}
