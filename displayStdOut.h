#ifndef	DISPLAYSTDOUTH_
#define	DISPLAYSTDOUTH_

/**
 * Write the incu8ator messages to the standard output
 * instead of the display connected to the rPi for 
 * the test phase.
 */
#include <iostream>
#include <string>
#include "displayBase.h"

class displayStdOut : public displayBase {
public:
	displayStdOut(void) {;}
	virtual ~displayStdOut(void) {;}
	void showMessage(std::string const message);
};
#endif
