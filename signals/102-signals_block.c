#include "signals.h"

/**
 * signals_block - block a given set of signals
 * @signals: 0 terminated array of int, each one
 * beign a signal number
 * Return: 0 on success, -1 on error
 */

int signals_block(int *signals)
{
	sigset_t sigset;

	if (sigemptyset(&sigset) == -1)
		return (-1);
	for (; *signals; signals++)
		if (sigaddset(&sigset, *signals) == -1)
			return (-1);
	return (sigprocmask(SIG_BLOCK, &sigset, NULL) == -1 ? -1 : 0);
}
