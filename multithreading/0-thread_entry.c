#include "multithreading.h"

/**
 * thread_entry - serves as entry point to a new thread
 *
 * @arg: address of a string that must be printed and followed by \n
 * Return: EXIT_SUCCESS
 */

void *thread_entry(void *arg)
{
	printf("%s\n", (char *)arg);
	pthread_exit(NULL);
	return (0);
}
