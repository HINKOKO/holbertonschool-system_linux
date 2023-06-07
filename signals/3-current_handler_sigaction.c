#include "signals.h"

/**
 * current_handler_sigaction - retrieve the current handler
 * Return: Returns a pointer to the current handler of SIGINT
 * or NULL on failure
 */

void (*current_handler_sigaction(void))(int)
{
	struct sigaction sa;
	struct sigaction old_sa;

	sigemptyset(&sa.sa_mask);

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;

	/* get current handler */
	if (sigaction(SIGINT, NULL, &old_sa) == -1)
		return (NULL);

	/* restore */
	if (sigaction(SIGINT, &old_sa, NULL) == -1)
		return (NULL);
	return (old_sa.sa_handler);
}
