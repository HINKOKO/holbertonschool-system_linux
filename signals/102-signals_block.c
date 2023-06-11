#include "signals.h"

/**
 * signals_block - block a given set of signals
 * @signals: 0 terminated array of int, each one
 * beign a signal number
 * Return: 0 on success, -1 on error
 */

int signals_block(int *signals)
{
	int i = 0;
	sigset_t sigset = {0};

	sigemptyset(&sigset);
	while (signals[i])
	{
		sigaddset(&sigset, signals[i]);
		i++;
	}
	sigprocmask(SIG_BLOCK, &sigset, NULL);
	return (0);
}
