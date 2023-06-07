#include "signals.h"

/**
 * current_handler_signal - retrieve the current handler
 * of signal SIGINT
 * Return: pointer to the current handler of SIGINT,
 * or NULL on failure
 */

void (*current_handler_signal(void))(int)
{
	/* declare function pointer to store current signal handler */
	void (*sighandler)(int);

	/* param NULL to ignore the signal */
	sighandler = signal(SIGINT, SIG_DFL);
	/* restore original signal handler with this call */
	signal(SIGINT, sighandler);
	return (sighandler);
}
