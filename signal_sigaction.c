/**
 * File: signal_sigaction.c
 * Modified by: Rose Zickefoose
 * 
 * Brief summary of program: Able to take a signal from terminal
 *						     Command to run program:
 *							 ./[name of program] &
 *
 *							 Command to send SIGUSR1:
 *							 kill -SIGUSR1 [pid]
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void handle_signal() {
	printf("Signal received\n");
	printf("pid: %d\n", getpid());
}

int main(void) {
	// Sets up the sigaction structure
	struct sigaction action;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = handle_signal;
	// Calls sigaction on SIGUSR1
	sigaction(SIGUSR1, &action, NULL);

	while(1) {
		sleep(1);
	}
}
