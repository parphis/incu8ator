#include "log.h"

bool log::dbg = false;
std::string log::ident = "incu8ator<main>";

void log::add(int fac, std::string msg) {
	openlog(log::ident.c_str(),0,LOG_LOCAL1);
	switch(fac) {
		case 0: syslog(LOG_ERR, msg.c_str());
			break;
		case 1: if(log::dbg)	syslog(LOG_WARNING, msg.c_str());
			break;
		case 2: if(log::dbg)	syslog(LOG_INFO, msg.c_str());
			break;
		default:
			syslog(LOG_INFO, msg.c_str());
	}
	closelog();
}
void log::err(std::string msg) {
	log::add(0,msg);
}
void log::wrn(std::string msg) {
	log::add(1, msg);
}
void log::inf(std::string msg) {
	log::add(2, msg);
}
void log::_debug(void) {
	log::dbg = true;
}
void log::_ident(std::string i) {
	log::ident = i;
}
