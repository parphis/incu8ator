#include "incu8ator.h"

void incu8ator::log(std::string msg, int l) {
	switch(l) {
		case 0:	incu8atorLog::err(msg);
			break;
		case 1: if(dbg)	incu8atorLog::wrn(msg);
			break;
		case 2: if(dbg)	incu8atorLog::inf(msg);
			break;
		default: incu8atorLog::inf(msg);
	}
}

incu8ator::incu8ator(void) : dbg(false) {
}

incu8ator::~incu8ator(void) {
	if(p!=NULL)	delete p;
	if(s!=NULL)	delete s;
	if(d!=NULL)	delete d;
}

void incu8ator::_debug(void) {
	dbg = true;
}

void incu8ator::_release(void) {
	dbg = false;
}
/**
 * Determine whether a sensor has connected or not.
 * Check if the program wheel is available or not.
 * Show the messages on the display.
 * Check the GPIO port used to switch the heat-thread.
 */
bool incu8ator::initIncu8ator(std::string const sensorType, std::string displayType) {
	log("Starting the incu8ator...",2);
	log("Initializing the display...",2);
	log(std::string("Wanted display type is \'").append(displayType).append("\'"),2);
	d = displayBase::createDisplay(displayType);
	d->showMessage(std::string("Welcome on \"").append(displayType).append("\""));
	d->showMessage("Waking up the sensor...");
	log("Waking up the sensor...",2);

	s = sensorBase::createSensor(sensorType);
	if(!s->helloSensor()) {
		d->showMessage("No sensor was detected.");
		log("No sensor was detected. Program ends.",0);
		return false;
	}
	else {
		d->showMessage(std::string("Used sensor type is \"").append(sensorType).append("\""));
		log(std::string("Used sensor type is \'").append(sensorType).append("\'"),2);
	}

	std::string errConfig = "";
	p = new programWheel();
	if(!p->initProgramWheel(errConfig)) {
		log(std::string("Unable to init the program wheel: \'").append(errConfig).append("\'"),0);
		return false;
	}
	return true;
}
/**
 * may be start here the elapsed time counter of the program wheel???
 */
void incu8ator::startIncu8ator(void) {
	log("Starting the program wheel...",2);
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
		log("Incu8ator has stoped because the program has done.",2);
		return false;
	}
	else {
		std::stringstream ss;
		ss << "Wanted/measured temp: " << wantedTemp << "/" << temp;
		log(ss.str(),2);
		log(std::string("Turn the heating ").append(((temp<wantedTemp) ? "ON" : "OFF")),2);
	}

	return true;
}
