/**
 * @file signal_segfault.c
 * @brief Program that dereferences a null pointer causing a segmentation fault
 */

/**
 * Modified by: Rose Zickefoose
 * 
 * Brief summary of modifications: Made a handler for SIGSEGV
 *								   Saw that when SIGSEGV is Caught,
 *								   it catches it an infinite amount of times,
 *								   creating a infinite loop of catching.
 */


#include <signal.h>
#include <stdio.h>

void handle_signal() {
	printf("SIGSEGV Caught\n");
}

int main (int argc, char* argv[]) {
	// Sets up signal to catch SIGSEGV
	signal(SIGSEGV, handle_signal);

    // Declare a null pointer
    int* i = NULL;

    // Dereference the null pointer
    printf("The value of i is: %d\n", *i);

    // Return to exit the program
    return 0;
}
