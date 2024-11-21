/***************************************************************** 
* Filename: tennis_sender.c
* Description: Sender for a tennis game using signals
* Author: Rose Zickefoose
* Date: 11/20/2024
* Note (Compile Instructions):
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

static int pid;
static union sigval sigval;

void handle_ball(int signo, siginfo_t *data, void* args) {
	if (data->si_value.sival_int == 10) {
		kill(pid, SIGKILL);
	} else {
		int max = 2;
		int min = 1;
		int time = rand() % (max - min + 1) + min;
		sleep(time);
		printf("\a");
		sigqueue(pid, SIGUSR1, sigval);
	}
}

int main(void) {
	// Gets the pid of recv_signal
	char line[100];
	system("pidof -s tr > /tmp/receiver_pid");
	FILE* fp = fopen("/tmp/receiver_pid", "r");
	if (fp == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	fgets(line, 100, fp);
	fclose(fp);
	pid = atoi(strtok(line, " "));

	// starts the count
	int volley_count = 0;
	sigval.sival_int = volley_count;

	// Sends the random number over to the receiver
	sigqueue(pid, SIGUSR1, sigval);

	// Sets up receiving end
	struct sigaction action;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &handle_ball;

	while(1) {
		sleep(1);
	}
}