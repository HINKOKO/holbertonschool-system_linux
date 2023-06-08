#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

/**
 * special_sigint - sets a handler for signal SIGINT
 * exits right after the signal is received and handled
 * @signum: signal number
 */

void special_sigint(int signum)
{
	printf("Caught %d\n", signum);
	printf("Signal received\n");
	/* _Exit uppercase, higher level alternative */
	/* performs some clean-up ops, flushes std I/O closes fd...*/
	_Exit(EXIT_SUCCESS);
}

/**
 * main - program that suspends indefinitely until signal received
 * Return: 0 success
 */

int main(void)
{
	struct sigaction sa;

	sa.sa_handler = special_sigint;
	/* set sigaction for SIGINT */
	sigaction(SIGINT, &sa, NULL);
	/* suspends indefinitely until a signal is received */
	pause();

	return (0);
}
