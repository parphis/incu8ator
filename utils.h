#include <unistd.h>
#include <signal.h>
#include <string>
#include <sstream>

// delaying is based on 
// https://gist.github.com/aspyct/3462238
void handle_sigalrm(int signal);
void do_sleep(int seconds);

inline void to_binary(uint8_t n, std::string& b) {
	char bit;
	b = "";
	
	while(1) {
		if ((n%2)==0) {
			bit = '0';
		}
		else	bit = '1';
		b.push_back(bit);
		n >>= 1;
		if (n==0)	break;
	}
}

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
