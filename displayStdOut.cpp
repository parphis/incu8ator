#include "displayStdOut.h"

void displayStdOut::showMessage(std::string const message) {
	std::cout << "\r" << message << std::flush << std::endl;
}
