#include "signals.h"

/**
 * print_hello - handler to catch Ctrl^C Task1
 * @signum: the signal
 *
 */
void print_hello(int signum)
{
	(void)signum;
	printf("Hello :)\n");
	fflush(stdout);
}

/**
 * set_print_hello - print hello when Ctrl^C
 */

void set_print_hello(void)
{
	/* set the handler to print_hello */
	signal(SIGINT, print_hello);
}
