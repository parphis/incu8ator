#include "programWheel.h"
#include "utils.h"
bool programWheel::startProgramWheel(void) {
	// first check if there is a file in /etc/incu8ator/step.cache.
	// if yes read in the step number and the elapsed time (this 
	// can be used to recover the status in case of power supply issue).
	std::string res;
	if(loadStatus(stepID, el->elapsedSeconds, res)) {
		std::cout << "Found state.xml" << std::endl;
	}
	else	std::cout << res << std::endl;

	// This cannot be used here because of a g++ 4.7.2 bug?
	//std::thread t1(el);	
	// sometimes compiling it with the class object as a functor 
	// g++ returns with the error of
	//   /usr/include/c++/4.7/type_traits:1834:9 error: 'std::declval<elapsedTimeThread*>() cannot be used a function'
	// so use the start member function as a thread parameter instead...
	// http://stackoverflow.com/questions/29966780/overload-resolution-issue-in-generic-vector-class (check the accepted answer)
	std::thread t1(&elapsedTimeThread::start, el);

	t1.detach();

	return true;
}
/**
 * Check if the progwheel.xml is available at the path /etc/incu8ator/
 * and check if there is a stamp.cache file or not.
 * @return false if the XML config file does not exists or true otherwise.
 */
bool programWheel::initProgramWheel(std::string& res) {
	result = doc.load_file(progWheelXMLPath);
	if(!result) {
		res = "progwheel.xml error: ";
		res.append(result.description());
		return false;
	}

	if(!processConfig(res)) {
		return false;
	}
	el = new elapsedTimeThread();

	return true;
}
bool programWheel::saveStatus(int stepID, double elapsedSeconds) {
	pugi::xml_document status;
	std::stringstream ss;
	ss << "<state><stepID>" << stepID << "</stepID><elapsed>" << elapsedSeconds << "</elapsed></state>";
	doc.load_string(ss.str().c_str());
	return doc.save_file(statusXMLPath);
}
bool programWheel::loadStatus(int& stepID, double& elapsedSeconds, std::string& res) {
	pugi::xml_document status;
	pugi::xml_parse_result status_res;

	status_res = doc.load_file(statusXMLPath);
	if(!status_res) {
		res = "state.xml error: ";
		res.append(status_res.description());
		stepID = 0;
		elapsedSeconds = 0.0;
		return false;
	}

	stepID = atoi(doc.child(STATE_NODE_NAME).child(STEPID_NODE_NAME).text().get());
	elapsedSeconds = atof(doc.child(STATE_NODE_NAME).child(ELAPSED_NODE_NAME).text().get());

	return true;
}
bool programWheel::processConfig(std::string& res) {
	if(result) {
		double hour, temp, hum;
		int i = 1;
		pugi::xml_node next_step;
		root = doc.child(ROOT_NODE_NAME);

		steps.clear();

		next_step = root.child((std::string(STEP_NODE_NAME).append(NumberToString(i)).c_str()));
		for (; (i<MAX_STEPS) && (next_step); i++) {
			hour = atof(next_step.child(HOUR_NODE_NAME).text().get());
			temp = atof(next_step.child(TEMP_NODE_NAME).text().get());
			hum = atof(next_step.child(HUM_NODE_NAME).text().get());

			Step nextStep = Step(hour, temp, hum, i-1);

			steps.push_back(nextStep);

			next_step = root.child((std::string(STEP_NODE_NAME).append(NumberToString(i+1)).c_str()));
		}
	}
	else {
		res = result.description();
		return false;
	}
	return true;
}
double programWheel::getWantedTemperature(void) {
	try {
		double wanted = 0.0;
		double s = el->getElapsedSeconds();
		double h = s/3600;

		std::cout << "Current elpased time in hours: " << h << std::endl;
		std::cout << "Current elpased time in sec: " << s << std::endl;
		std::cout << "Current stepID and interval: " << stepID << " - " << steps.at(stepID).interval << std::endl;

		if(h >= steps.at(stepID).interval) {
			s = el->elapsedSeconds = 0.0;
			stepID+=1;
		}

		wanted = steps.at(stepID).temp;
		// save the current status - stepID and elapsed time in seconds
		if(!saveStatus(stepID, s)) {
			std::cout << "Unable to save the status file to " << statusXMLPath << std::endl;
		}

		return wanted;
	}
	catch(const std::out_of_range& e) {
		el->stop();
		// remove the state.xml because the program has done
		unlink(statusXMLPath);
		return 0.0;
	}
}
double programWheel::getWantedHumidity(void) {
	return 60.0;
}
