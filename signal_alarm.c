/**
 * File: signal_alarm.c
 * Modified by: Rose Zickefoose
 * 
 * Brief summary of program: Creates an alarm signal for 5 seconds then
 *							 displays that the signal was caught
 */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle_signal() {
	printf("SIGALRM received\n");
}

int main(void) {
	// Sets up the signal to be caught
	signal(SIGALRM, handle_signal);
	// Sets an alarm for 5 seconds
	alarm(5);
	// Makes sure that the alarm is finsihed
	sleep(5);
	return 0;
}
