#include "log.h"

bool log::dbg = false;
bool log::report = false;
bool log::report_exist = false;
std::string log::ident = "incu8ator<main>";
std::string log::fn = "";

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
void log::_report(void) {
	log::report = true;
}
void log::_report_exist(bool exist) {
	log::report_exist = exist;
}
void log::_report_name(std::string fname) {
	log::fn = fname;
}
/**
 * Save the result of the sensor query.
 * @param q is custom formatted string. For example a CSV formatted line.
 *	 	"DT","TEMP","HUM","ERR"
 *		2016.10.28.22:33:34,12.5,67,""
 *		2016.10.28.22:43:55,0,0,"Checksum error"
 */
void log::_reportQuery(std::string q) {
	if(!log::report) return;

	FILE *fp;
	fp = fopen(log::fn.c_str(), "a");
	
	if(fp==NULL) {
		log::err("Not able to save the report file.");
		return;
	}

	if(!log::report_exist) {
		fputs("\"DT\",\"TEMP\",\"HUM\",\"ERR\"\n\0", fp);
		log::report_exist = true;
	}
	fputs(q.c_str(), fp);
	fclose(fp);
}
