#include <unistd.h>
#include <signal.h>
#include <string>
#include <sstream>

// delaying is based on 
// https://gist.github.com/aspyct/3462238
void handle_sigalrm(int signal);
void do_sleep(int seconds);

// http://www.cplusplus.com/articles/D9j2Nwbp
template <typename T>
std::string NumberToString(T Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

template <typename T>
T StringToNumber(std::string& Text) {
	std::istringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}
