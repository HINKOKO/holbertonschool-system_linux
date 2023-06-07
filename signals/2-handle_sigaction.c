#include "signals.h"
#include <signal.h>

/**
 * sigint_handler - handler for SIGINT signal
 * @signum: the signal num
 */

void sigint_handler(int signum)
{
	printf("Gotcha! [%i]\n", signum);
	fflush(stdout);
}

/**
 * handle_sigaction - handle signal with sigaction
 * Return: 0 success, -1 error
 */

int handle_sigaction(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	return (sigaction(SIGINT, &sa, NULL));
}
