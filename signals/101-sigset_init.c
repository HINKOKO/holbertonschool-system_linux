#include "signals.h"

/**
 * sigset_init - initialize a sigset
 * @set: pointer to the signal set to init
 * @signals: 0 terminated array of int, each one
 * beign a signal number
 * Return: 0 on success, -1 on error
 */

int sigset_init(sigset_t *set, int *signals)
{
	int i = 0;

	sigemptyset(set);
	while (signals[i])
	{
		sigaddset(set, signals[i]);
		i++;
	}
	return (0);
}
