#include "signals.h"

/**
 * signals_unblock - unblock a given set of signals
 * from being delivered to processs
 * @signals: 0 terminated array of int, each one
 * beign a signal number
 * Return: 0 on success, -1 on error
 */

int signals_unblock(int *signals)
{
	sigset_t sigset;

	if (sigemptyset(&sigset) == -1)
		return (-1);
	for (; *signals; signals++)
		if (sigaddset(&sigset, *signals) == -1)
			return (-1);
	return (sigprocmask(SIG_UNBLOCK, &sigset, NULL) == -1 ? -1 : 0);
}
