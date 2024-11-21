/**
 * File: recv_signal.c
 * Modified by: Rose Zickefoose
 * 
 * Brief summary of program: Signal reciever program. Receives a SIGUSR1
 *						     signal from the sender
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle_signal(int signo, siginfo_t *data, void* args) {
	printf("Received signal\n");
	printf("sival_int: %d\n", data->si_value.sival_int);
	exit(1);
}

int main(void) {
	// Sets up the signal action for SIGUSR1
	struct sigaction action;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &handle_signal;
	// Creates the signal action for SIGUSR1
	sigaction(SIGUSR1, &action, NULL);
	while(1) {
		sleep(1);
	}
}
