#ifndef ELAPSEDTIMETHREADH_
#define ELAPSEDTIMETHREADH_

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <thread>
#include <mutex>

class elapsedTimeThread {
private:
	bool halt;
	std::mutex m;
public:
	double elapsedSeconds;
	elapsedTimeThread(void);
	~elapsedTimeThread(void);
	double getElapsedSeconds(void);
	void operator()();
	void start(void);
	void stop(void);
};
#endif
