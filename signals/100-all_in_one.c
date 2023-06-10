#include "signals.h"

/**
 * handle_them_all - helper function to achieve the goal
 * of `all_in_one` function
 * @signum: number
 * @info: info struct about signal send
 * @context: unused
 */

void handle_them_all(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)signum;

	psiginfo(info, "Caught");
}

/**
 * all_in_one - handle all signals and display info accordingly
 */

void all_in_one(void)
{
	int sig;
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = handle_them_all;
	act.sa_flags = SA_SIGINFO;

	/* this for loop might return -1 but nevermind */
	for (sig = 1; sig <= SIGRTMAX; ++sig)
		sigaction(sig, &act, NULL);
}
