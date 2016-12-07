#include "utils.h"


void handle_sigalrm(int signal) {
	// got sigalrm, do_sleep will end...
}
void do_sleep(int seconds) {
	struct sigaction sa;
	sigset_t mask;

	sa.sa_handler = &handle_sigalrm;
	sa.sa_flags = SA_RESETHAND;
	sigfillset(&sa.sa_mask);
	sigaction(SIGALRM, &sa, NULL);
	sigprocmask(0, NULL, &mask);
	sigdelset(&mask, SIGALRM);
	alarm(seconds);
	sigsuspend(&mask);
}
