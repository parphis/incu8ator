#include "incu8atorLog.h"

void incu8atorLog::add(int fac, std::string msg) {
	openlog("inu8ator",0,LOG_LOCAL1);
	switch(fac) {
		case 0: syslog(LOG_ERR, msg.c_str());
			break;
		case 1: syslog(LOG_WARNING, msg.c_str());
			break;
		case 2: syslog(LOG_INFO, msg.c_str());
			break;
		default:
			syslog(LOG_INFO, msg.c_str());
	}
	closelog();
}
void incu8atorLog::err(std::string msg) {
	incu8atorLog::add(0,msg);
}
void incu8atorLog::wrn(std::string msg) {
	add(1, msg);
}
void incu8atorLog::inf(std::string msg) {
	add(2, msg);
}
