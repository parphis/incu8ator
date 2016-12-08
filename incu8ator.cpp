#include "incu8ator.h"


inline void incu8ator::clearSS(std::stringstream& ss) {
	if(ss) {
		ss.str("");
		ss.clear();
	}
}
void incu8ator::sdt(std::string& s) {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y.%m.%d %X", &tstruct);
    s = buf;
}
void incu8ator::toogleHeating(int level) {	
	bcm2835_gpio_write(_heatGPIOPin, level);
}
void incu8ator::heatOn(void) {
	toogleHeating(HIGH);
	heating = true;
}
void incu8ator::heatOff(void) {
	toogleHeating(LOW);
	heating = false;
}

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
bool incu8ator::initIncu8ator(std::string const sensorType, std::string displayType, int sensorGPIOPin, int heatGPIOPin, int readAlgorythm, double maxt, int maxse) {
	log::inf("Starting the incu8ator...");
	log::inf("Initializing the display...");
	log::inf(std::string("Wanted display type is \'").append(displayType).append("\'"));
	d = displayBase::createDisplay(displayType);
	d->showMessage(std::string("Welcome on \"").append(displayType).append("\""));
	d->showMessage("Waking up the sensor...");
	log::inf("Waking up the sensor...");

	s = sensorBase::createSensor(sensorType);
	s->setGPIOPin(sensorGPIOPin);
	s->setAlgorythm(readAlgorythm);
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


	_heatGPIOPin = heatGPIOPin;
	bcm2835_gpio_fsel(_heatGPIOPin, BCM2835_GPIO_FSEL_OUTP);
	
	maxTemp = maxt;
	maxSensorError = maxse;

	prevTemp = 0.0;
	heating = true;
	return true;
}
/**
 * Start here the elapsed time counter of the program wheel (thread t1).
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
	std::string lastError = "";
	std::string dt = "";
	std::stringstream ss;

	sdt(dt);

	// ask the sensor for the temp (and humidity if available)
	s->readOut();

	// check if there was an error in the sensor query
	if(s->getCrcError(lastError)) {
		int ec = s->getCrcErrorCounter();
		// the maxSensorError is 5 by default;
		// the query interval can not be bigger than 10seconds
		// so 5*10seconds=50seconds, this is the maximum time
		// the heating device can be turned on; assuming a ceramic heating 
		// wire within an insulated ca. 0.6m3 box the temperature increases 
		// ca. 1°C/15 seconds; this should mean not more than 5°C increase within the 
		// 50 seconds; assuming that the eggs needs ca. 38°C and the process 
		// ran well until this critical sensor error the inner temperature 
		// will be ca. 43°C which is not so critical and flammable.
		if(ec>=maxSensorError) {
			// turn off the heating just to avoid
			// overheating in case of sensor error
			heatOff();
			clearSS(ss);
			ss << "Too many errors after each other! (" << s->getCrcErrorCounter() << ")";
			d->showMessage(ss.str());
		}

		clearSS(ss);
		ss << "Sensor query error: " << lastError;
		log::err(ss.str());
		
		clearSS(ss);
		ss << dt << ",0.0," << "0.0,\"" << lastError << "\"" << std::endl;
		log::_reportQuery(ss.str());
		// return with true because we do not need to stop the
		// thermostat but need to stop the temperature control process
		return true;
	}

	// inform the user the status of the internals
	s->getFormattedLines(lines);
	clearSS(ss);
	ss << lines << std::endl << std::setprecision(3) <<  p->getElapsedHours() << "/" << p->getInterval() << "h";
	d->showMessage(ss.str());

	temp = s->getTemperature();
	hum = s->getHumidity();
	wantedTemp = p->getWantedTemperature();

	clearSS(ss);
	ss << dt << "," << temp << "," << hum << ",\"" << "\"" << std::endl;
	log::_reportQuery(ss.str());

	if(wantedTemp==0.0) {
		d->showMessage("Program has done.\nIncu8ator has stoped.");
		log::inf("Incu8ator has stoped because the program has done.");
		return false;
	}
	else {
		clearSS(ss);
		ss << "Wanted/measured temp: " << wantedTemp << "/" << temp;
		log::inf(ss.str());
		// turn on or off the heating device here
		if(temp<=wantedTemp) {
			heatOn();
		}
		if(prevTemp<temp) {
			heatOff();
		}
		if(temp>=wantedTemp) {
			heatOff();
		}
		// emergency limit!
		if(temp>=maxTemp) {
			heatOff();
		}
		prevTemp = temp;
		log::inf(std::string("Turn the heating ").append(((heating) ? "ON" : "OFF")));
	}

	return true;
}
