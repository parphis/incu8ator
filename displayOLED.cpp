#include "displayOLED.h"

bool displayOLED::_init(void) {
	return display.init(OLED_SPI_DC, OLED_SPI_RESET, OLED_SPI_CS, 1);
}
displayOLED::displayOLED(void) {
	log::_ident("displayOLED");
	mAvailable = _init();
	if(mAvailable==false) {
		log::err("Could not initialize the OLED driver\n");
	}
}
void displayOLED::showMessage(std::string const message) {
	if(mAvailable==false) {
		log::inf(message);
	}
	else {
		display.begin();
		display.setTextSize(2);
		display.setTextColor(WHITE);
		//display.clearDisplay();
		display.setCursor(1, 1);
		display.print(message.c_str());
		display.display();
	}
}
