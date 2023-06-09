#include "signal.h"
#include <stdio.h>

/**
 * sigint_handler - handler function for printing gotcha
 * when Ctrl^C is pressed
 * @signum: the signum to print
 */

void sigint_handler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
	fflush(stdout);
}

/**
 * handle_signal - set a handler for the signal SIGINT Ctrl^C
 * Return: 0 on success, -1 on error
 */

int handle_signal(void)
{
	return (signal(SIGINT, sigint_handler) == SIG_ERR ? -1 : 0);
}
