#include "incu8ator.h"

incu8ator::incu8ator(void) {
}

incu8ator::~incu8ator(void) {
	if(p!=NULL)	delete p;
	if(s!=NULL)	delete s;
	if(d!=NULL)	delete d;
}

/**
 * Determine whether a sensor has connected or not.
 * Check if the program wheel is available or not.
 * Show the messages on the display.
 * Check the GPIO port used to switch the heat-thread.
 */
bool incu8ator::initIncu8ator(std::string const sensorType, std::string displayType) {
	log::inf("Starting the incu8ator...");
	log::inf("Initializing the display...");
	log::inf(std::string("Wanted display type is \'").append(displayType).append("\'"));
	d = displayBase::createDisplay(displayType);
	d->showMessage(std::string("Welcome on \"").append(displayType).append("\""));
	d->showMessage("Waking up the sensor...");
	log::inf("Waking up the sensor...");

	s = sensorBase::createSensor(sensorType);
	if(!s->helloSensor()) {
		d->showMessage("No sensor was detected.");
		log::err("No sensor was detected. Program ends.");
		return false;
	}
	else {
		d->showMessage(std::string("Used sensor type is \"").append(sensorType).append("\""));
		log::inf(std::string("Used sensor type is \'").append(sensorType).append("\'"));
	}

	std::string errConfig = "";
	p = new programWheel();
	if(!p->initProgramWheel(errConfig)) {
		log::err(std::string("Unable to init the program wheel: \'").append(errConfig).append("\'"));
		return false;
	}
	return true;
}
/**
 * may be start here the elapsed time counter of the program wheel???
 */
void incu8ator::startIncu8ator(void) {
	log::inf("Starting the program wheel...");
	p->startProgramWheel();
}
/**
 * @return false if the program wheel notices that there is no
 * more program steps set. That means the while loop in the main 
 * must be stoped.
 */
bool incu8ator::controlTemp(void) {
	if(s==NULL) return false;
	if(p==NULL) return false;

	double temp = 0.0;
	double wantedTemp = 0.0;
	double hum = 0.0;

	std::string lines = "";

	// ask the sensor for the temp (and humidity if available)
	s->readOut();
	// inform the user the status of the internals
	s->getFormattedLines(lines);
	d->showMessage(lines);

	temp = s->getTemperature();
	hum = s->getHumidity();
	wantedTemp = p->getWantedTemperature();

	if(wantedTemp==0.0) {
		d->showMessage("Incu8ator has stoped.");
		log::inf("Incu8ator has stoped because the program has done.");
		return false;
	}
	else {
		std::stringstream ss;
		ss << "Wanted/measured temp: " << wantedTemp << "/" << temp;
		log::inf(ss.str());
		log::inf(std::string("Turn the heating ").append(((temp<wantedTemp) ? "ON" : "OFF")));
	}

	return true;
}
