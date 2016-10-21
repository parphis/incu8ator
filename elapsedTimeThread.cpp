#include "elapsedTimeThread.h"
#include "utils.h"

void elapsedTimeThread::start(void) {
	while(halt==false) {
		// lock variable elapsedTimeThread to avoid 
		// conflicts with programWheel - programWheel 
		// object should be able to set the elapsedTimeThread to
		// zero in order to start this timer when the incubator 
		// program reaches the next step.
		m.lock();
		elapsedSeconds+=1;
		m.unlock();
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
void elapsedTimeThread::stop(void) {
	m.lock();
	halt = true;
	m.unlock();
}
void elapsedTimeThread::operator()() {
	while(halt==false) {
		elapsedSeconds++;
		
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
double elapsedTimeThread::getElapsedSeconds(void) {
	return elapsedSeconds;
}
elapsedTimeThread::elapsedTimeThread(void) {
	elapsedSeconds = 0.0;
	halt = false;
}
elapsedTimeThread::~elapsedTimeThread(void) {
	;
}
