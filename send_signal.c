/**
 * File: send_signal.c
 * Modified by: Rose Zickefoose
 * 
 * Brief summary of program: Sends a randomly generated number
 *						     to the receiver
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <bits/types/__sigval_t.h>

int main(void) {
	// Gets the pid of recv_signal
	char line[100];
	system("pidof -s recv_signal > /tmp/pid");
	FILE* fp = fopen("/tmp/pid", "r");
	if (fp == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	fgets(line, 100, fp);
	fclose(fp);
	int pid = atoi(strtok(line, " "));

	// Creates a random number and stores it to the
	// sival_int
	srand(time(NULL));
	int value = rand();
	union sigval sigval;
	sigval.sival_int = value;
	printf("Random Number: %d\n", value);

	// Sends the random number over to the receiver
	sigqueue(pid, SIGUSR1, sigval);
}
