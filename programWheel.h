/**
 * Program Wheel is a class which can read out the 
 * progwheel.xml configuration file and provide the 
 * parameter values for the incu8ator controller class.
 * The progwheel.xml file must be on the path /etc/incu8ator/
 * This class counts the elapsed time and it can tell the 
 * current necessary temperature and humidty values as well as 
 * the elapsed time.
 */
#ifndef PROGRAMWHEELH_
#define PROGRAMWHEELH_

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <stdexcept>
#include <thread>
#include "./pugi/pugixml-1.7/src/pugixml.hpp"
#include "elapsedTimeThread.h"
#include "log.h"

class programWheel {
private:
	pugi::xml_document doc;
	pugi::xml_parse_result result;
	pugi::xml_node root;
	const char *progWheelXMLPath;
	const char *statusXMLPath;
	int stepID;
	const int MAX_STEPS;
	const char *ROOT_NODE_NAME;
	const char *STEP_NODE_NAME;
	const char *HOUR_NODE_NAME;
	const char *TEMP_NODE_NAME;
	const char *HUM_NODE_NAME;
	const char *STATE_NODE_NAME;
	const char *STEPID_NODE_NAME;
	const char *ELAPSED_NODE_NAME;

	struct Step {
		double interval;
		double temp;
		double hum;
		int id;
		Step(double i, double t, double h, int in_id) : 
			interval(i), temp(t), hum(h), id(in_id) {;}
	};

	std::vector<Step> steps;
	elapsedTimeThread *el;

	bool processConfig(std::string& errConf);
	bool saveStatus(int stepID, double elapsedSeconds);
	bool loadStatus(int& stepID, double& elapsedSeconds, std::string& res);
public:
	programWheel(void) : progWheelXMLPath("/etc/incu8ator/progwheel.xml\0"),statusXMLPath("/etc/incu8ator/state.xml\0"), stepID(0), MAX_STEPS(100), ROOT_NODE_NAME("incu8ator\0"), STEP_NODE_NAME("step\0"), HOUR_NODE_NAME("hour\0"), TEMP_NODE_NAME("temp\0"), HUM_NODE_NAME("hum\0"), STATE_NODE_NAME("state\0"), STEPID_NODE_NAME("stepID\0"), ELAPSED_NODE_NAME("elapsed\0") {log::_ident("incu8ator<programWheel>");}
	~programWheel(void) {if(el) delete el;}
	double getWantedTemperature(void);
	double getWantedHumidity(void);
	double getElapsedHours(void);
	double getInterval(void);
	bool initProgramWheel(std::string& res);
	bool startProgramWheel(void);
};
#endif
