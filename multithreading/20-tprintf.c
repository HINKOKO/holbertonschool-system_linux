#include "multithreading.h"
#include <stdarg.h>

static pthread_mutex_t mutex;

__attribute__((constructor)) void init_mutex(void)
{
	pthread_mutex_init(&mutex, NULL);
}

__attribute__((destructor)) void destroy_mutex(void)
{
	pthread_mutex_destroy(&mutex);
}

/**
 * tprintf - v2 uses printf family
 * vprintf here to match the va_list args
 * @format:  pointer to string that serves as format specifier
 *
 * Return: 0 success
 */

int tprintf(char const *format, ...)
{
	/* Arguments are varying in number AND IN TYPE => va_list the way to go*/
	va_list args;

	va_start(args, format);

	/* lock the mutex */
	pthread_mutex_lock(&mutex);
	/* pthread_self() to retrieve proper ID */
	printf("[%lu] ", pthread_self());
	/* vprintf from man 3 printf is the way to go with va_list */
	vprintf(format, args);

	va_end(args);

	pthread_mutex_unlock(&mutex);
	return (0);
}
