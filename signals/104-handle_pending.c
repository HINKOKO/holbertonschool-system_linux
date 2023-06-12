#include "signals.h"

#define MAX_SIGNALS SIGRTMAX

/**
 * handle_pending - sets up a handler for all pending
 * signals of current process
 * @handler: pointer to the handler function
 * Return: 0 for success, -1 error
 */

int handle_pending(void (*handler)(int))
{
	sigset_t pending_set;
	struct sigaction sa;
	int sig;

	sa.sa_handler = handler;
	sigemptyset(&pending_set);
	sigpending(&pending_set);

	/* loop through all possible signals */
	for (sig = 1; sig < MAX_SIGNALS; sig++)
	{
		if (sigismember(&pending_set, sig) && sig != SIGKILL && sig != SIGSTOP)
			if (sigaction(sig, &sa, NULL) == -1)
				return (-1);
	}
	return (0);
}
