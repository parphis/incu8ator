/**
 * Create log messages using the syslog.
 */
#ifndef INCU8ATORLOGH_
#define INCU8ATORLOGH_

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <string>
#include <syslog.h>

class log {
private:
	static bool dbg;
	static bool report;
	static std::string ident;
	static bool report_exist;
	static std::string fn;
	static void add(int fac, std::string msg);
public:
	log(void);
	virtual ~log(void);
	static void err(std::string msg);
	static void wrn(std::string msg);
	static void inf(std::string msg);
	static void _report_exist(bool exist);
	static void _report_name(std::string fname);
	static void _report(void);
	static void _debug(void);
	static void _ident(std::string id);
	static void _reportQuery(std::string q);
};
#endif
