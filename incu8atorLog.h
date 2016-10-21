/**
 * Create log messages using the syslog facility.
 */
#ifndef INCU8ATORLOGH_
#define INCU8ATORLOGH_

#include <string>
#include <iostream>
#include <syslog.h>

class incu8atorLog {
private:
	static void add(int fac, std::string msg);
public:
	incu8atorLog(void);
	virtual ~incu8atorLog(void);
	static void err(std::string msg);
	static void wrn(std::string msg);
	static void inf(std::string msg);
};
#endif
