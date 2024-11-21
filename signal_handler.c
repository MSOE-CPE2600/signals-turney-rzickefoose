/**
 * @file signal_handler.c
 * @brief Sets a signal handler for SIGINT, the handler prints a message and then quits
 */

/**
 * Modified by: Rose Zickefoose
 * 
 * Brief summary of modifications: Added a way to change the behavior
 *								   of SIGINT. Also added a way to
 *								   kill the program using SIGKILL.
 */


#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


/**
 * @brief Signal handler for SIGINT - prints a message and exits
 */

void handle_signal() {
    printf("Received a signal\n");
}

int main() {
	// Changes the behavior of SIGINT
	struct sigaction action;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	action.sa_sigaction = handle_signal;

    // Register for the signal
    sigaction(SIGINT, &action, NULL);

    // Wait until a signal is received
    while(1) {
        printf("Sleeping\n");
        sleep(1);

    	// kills the program after 2 sleeps
    	pid_t pid = fork();
    	if(pid == 0) {
    		kill(pid, SIGKILL);
    	}
    }

    return 0;
}
