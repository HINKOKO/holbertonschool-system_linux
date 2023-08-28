#include "multithreading.h"

/**
 * tprintf - uses printf fonky family to print out given fmt string
 *
 * @format: format of the string
 * Return: 0 success
 */

int tprintf(char const *format, ...)
{
	/* pthread_self() provides proper thread ID concerned by the call */
	printf("[%lu] %s", pthread_self(), (char *)format);
	return (0);
}
