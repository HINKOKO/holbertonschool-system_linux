#include "multithreading.h"

/**
 * tprintf - uses printf fonky family to print out given fmt string
 *
 * @format: format of the string
 * Return: 0 success
 */

int tprintf(char const *format, ...)
{
	printf("[%lu] %s", (unsigned long)format, (char *)format);
	return (0);
}
