/***************************************************************** 
* Filename: tennis_receiver
* Description: Receiver for a tennis game using signals
* Author: Rose Zickefoose
* Date: 11/20/2024
* Note (Compile Instructions): 
*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

// This makes noise: printf("\a");

static int pid;

void handle_ball(int signo, siginfo_t *data, void* args) {
	int max = 2;
	int min = 1;
	int time = rand() % (max - min + 1) + min;
	data->si_value.sival_int += 1;
	sleep(time);
	printf("\a");
	sigqueue(pid, SIGUSR1, data->si_value);
}

int main(void) {
	// Gets the pid of recv_signal
	char line[100];
	system("pidof -s ts > /tmp/server_pid");
	FILE* fp = fopen("/tmp/server_pid", "r");
	if (fp == NULL) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	fgets(line, 100, fp);
	fclose(fp);
	pid = atoi(strtok(line, " "));

	// Sets up receiving end
	struct sigaction action;
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &handle_ball;

	while(1) {
		sleep(1);
	}
}