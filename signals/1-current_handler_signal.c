#include "signal.h"

/**
 * current_handler_signal - retrieve the current handler
 * of signal SIGINT
 * Return: pointer to the current handler of SIGINT,
 * or NULL on failure
 */

void (*current_handler_signal(void))(int)
{
	return (signal(SIGINT, SIG_DFL));
}
