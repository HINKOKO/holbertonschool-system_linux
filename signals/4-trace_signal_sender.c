#include "signals.h"

/**
 * sigquit_handler - custom handler function for signal SIGQUIT
 * handler prototype for Real-Time signals with sigaction
 * @signum: num of signal, HAS TO BE SIGQUIT ONLY
 * @info: pointer to struct which contains information about the signal
 * including the PID of the caller ==> Who said that ?!
 * @context: rarely used, contains info about execution context
 */

void sigquit_handler(int signum, siginfo_t *info, void *context)
{
	/* Unused here */
	(void)context;

	if (signum == SIGQUIT)
		printf("SIGQUIT sent by %i\n", info->si_pid);
}

/**
 * trace_signal_sender - defines a handler for SIGQUIT
 * reveal the PID of process that sent the signal
 * Return: 0 on success, -1 on error
 */

int trace_signal_sender(void)
{
	struct sigaction sa;

	sa.sa_sigaction = sigquit_handler;
	sa.sa_flags = SA_SIGINFO;

	return (sigaction(SIGQUIT, &sa, NULL));
}
