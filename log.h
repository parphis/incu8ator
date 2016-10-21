/**
 * Create log messages using the syslog.
 */
#ifndef INCU8ATORLOGH_
#define INCU8ATORLOGH_

#include <string>
#include <iostream>
#include <syslog.h>

class log {
private:
	static bool dbg;
	static std::string ident;
	static void add(int fac, std::string msg);
public:
	log(void);
	virtual ~log(void);
	static void err(std::string msg);
	static void wrn(std::string msg);
	static void inf(std::string msg);
	static void _debug(void);
	static void _ident(std::string id);
};
#endif
